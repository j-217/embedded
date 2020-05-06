#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include "fspwm.h"

#define DEV_MA (1234)

struct fspwm_dev {
    struct cdev cdev;
    unsigned int __iomem *tcfg0;
    unsigned int __iomem *tcfg1;
    unsigned int __iomem *tcon;
    unsigned int __iomem *tcntb0;
    unsigned int __iomem *tcmpb0;
    unsigned int __iomem *tcnto0;

    struct clk *clk;
    unsigned long freq;
    struct pinctrl *pinctrl;
};

struct class *fspwm_cls;

static int fspwm_open(struct inode *inode, struct file *filp) {
    struct fspwm_dev *fspwm = container_of(inode->i_cdev, struct fspwm_dev, cdev);
    filp->private_data = fspwm;
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static int fspwm_release(struct inode *inode, struct file *filp) {
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static long fspwm_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    struct fspwm_dev *fspwm = filp->private_data;
    unsigned int div = 0;

    if (_IOC_TYPE(cmd) != FSPWM_MAGIC)
        return -ENOTTY;

    switch (cmd) {
        case FSPWM_START:
            writel(readl(fspwm->tcon) | 0x1, fspwm->tcon);
            break;
        case FSPWM_STOP:
            writel(readl(fspwm->tcon) & ~0x1, fspwm->tcon);
            break;
        case FSPWM_SET_FREQ:
            if (arg > fspwm->freq || arg <= 0)
                return -ENOTTY;

            div = fspwm->freq / arg - 1;
            writel(div,fspwm->tcntb0);
            writel(div/2,fspwm->tcmpb0);
            writel(readl(fspwm->tcon) | 0x2,fspwm->tcon);
            writel(readl(fspwm->tcon) & ~0x2,fspwm->tcon);
            break;
        default:
            return -ENOTTY;
    }
    printk("-----%s-----\n", __FUNCTION__);

    return 0;
}

struct file_operations fspwm_ops = {
    .owner = THIS_MODULE,
    .open = fspwm_open,
    .release = fspwm_release,
    .unlocked_ioctl = fspwm_ioctl,
};

static int fspwm_probe(struct platform_device *pdev) {
    dev_t dev;
    int ret;
    struct fspwm_dev *fspwm;
    struct resource *res;
    unsigned int prescaler0;

    dev = MKDEV(DEV_MA, 0);
    ret = register_chrdev_region(dev, 1, "fspwm");
    if (ret)
        goto err_reg_chr;
    device_create(fspwm_cls, NULL, dev, NULL, "fspwm");

    fspwm = kzalloc(sizeof(struct fspwm_dev), GFP_KERNEL);
    if (!fspwm) {
        ret = -ENOMEM;
        goto err_alloc;
    }

    cdev_init(&fspwm->cdev, &fspwm_ops);
    fspwm->cdev.owner = THIS_MODULE;
    ret = cdev_add(&fspwm->cdev, dev, 1);
    if (ret)
        goto err_add;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        ret = -ENOENT;
        goto err_res;
    }

    fspwm->tcfg0 = ioremap(res->start, resource_size(res));
    if (!fspwm->tcfg0) {
        ret = -EBUSY;
        goto err_map;
    }
    fspwm->tcfg1 = fspwm->tcfg0 + 1;
    fspwm->tcon = fspwm->tcfg0 + 2;
    fspwm->tcntb0 = fspwm->tcfg0 + 3;
    fspwm->tcmpb0 = fspwm->tcfg0 + 4;
    fspwm->tcnto0 = fspwm->tcfg0 + 5;

    fspwm->clk = clk_get(&pdev->dev, "timers");
    if (IS_ERR(fspwm->clk)) {
        ret = PTR_ERR(fspwm->clk);
        goto err_get_clk;
    }
    ret = clk_prepare_enable(fspwm->clk);
    if (ret < 0)
        goto err_clk_enable;
    fspwm->freq = clk_get_rate(fspwm->clk);

    prescaler0 = readl(fspwm->tcfg0) & 0xff;
    writel((readl(fspwm->tcfg1) & ~0xf) | 0x4, fspwm->tcfg1);
    fspwm->freq /= (prescaler0 + 1) * 16;
    writel((readl(fspwm->tcon) & ~0xf) | 0x8, fspwm->tcon);
    fspwm->pinctrl = devm_pinctrl_get_select_default(&pdev->dev);

    platform_set_drvdata(pdev, fspwm);
    printk("-----%s-----\n", __FUNCTION__);

    return 0;

err_clk_enable:
    clk_put(fspwm->clk);
err_get_clk:
    iounmap(&fspwm->tcfg0);
err_map:
err_res:
    cdev_del(&fspwm->cdev);
err_add:
    kfree(fspwm);
err_alloc:
    device_destroy(fspwm_cls, dev);
err_reg_chr:
    return ret;
}

static int fspwm_remove(struct platform_device *pdev) {
    dev_t dev;
    struct fspwm_dev *fspwm = platform_get_drvdata(pdev);

    dev = MKDEV(DEV_MA, 0);

    clk_disable_unprepare(fspwm->clk);
    clk_put(fspwm->clk);
    iounmap(fspwm->tcfg0);
    cdev_del(&fspwm->cdev);
    kfree(fspwm);
    device_destroy(fspwm_cls, dev);
    unregister_chrdev_region(dev, 1);
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static const struct of_device_id fspwm_of_matches[] = {
    { .compatible = "fs4412, fspwm", },
    {},
};

MODULE_DEVICE_TABLE(of, fspwm_of_matches);

struct platform_driver fspwm_drv = {
    .driver = {
        .name = "fspwm",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fspwm_of_matches),
    },
    .probe = fspwm_probe,
    .remove = fspwm_remove,
};

static int __init fspwm_init(void) {
    fspwm_cls = class_create(THIS_MODULE, "fspwm");
    platform_driver_register(&fspwm_drv);
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static void __exit fspwm_exit(void) {
    platform_driver_unregister(&fspwm_drv);
    class_destroy(fspwm_cls);
    printk("-----%s-----\n", __FUNCTION__);
}

module_init(fspwm_init);
module_exit(fspwm_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ruj");