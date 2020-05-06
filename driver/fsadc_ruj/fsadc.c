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
#include <linux/interrupt.h>
#include <linux/completion.h>

#include "fsadc.h"

#define DEV_MA (1111)

static struct class *fsadc_cls;

struct fsadc_dev {
    struct cdev cdev;
    unsigned int __iomem *adccon;
    unsigned int __iomem *adcdat;
    unsigned int __iomem *adcint;
    unsigned int __iomem *adcmux;

    unsigned int irq;           // AD转换需要一段时间，在ADC转换完成后产生中断
    unsigned int adcval;        // 转换成功的adc值
    struct completion completion;   // 用来进行同步
};

static int fsadc_open(struct inode *inode, struct file *filp) {
    struct fsadc_dev *fsadc = container_of(inode->i_cdev, struct fsadc_dev, cdev);
    filp->private_data = fsadc;
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static int fsadc_release(struct inode *inode, struct file *filp) {
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static long fsadc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    struct fsadc_dev *fsadc = filp->private_data;
    union chan_val cv;
    int ret;

    if (_IOC_TYPE(cmd) != FSADC_MAGIC)
        return -ENOTTY;

    switch (cmd) {
        case FSADC_GET_VAL:
            ret = copy_from_user(&cv, (union chan_val __user *)arg, sizeof(union chan_val));
            if (ret)
                return -EFAULT;
            if (cv.chan > 3)
                return -ENOTTY;

            // 选择通道
            writel(cv.chan, fsadc->adcmux);
            // 启动转换
            writel(readl(fsadc->adccon) | 1, fsadc->adccon);
            // 转换完成产生中断，也可以通过查看addcon 15位查看转换完成
            ret = wait_for_completion_interruptible(&fsadc->completion);
            if (ret)
                return ERESTARTSYS;
            cv.val = fsadc->adcval & 0xfff;

            ret = copy_to_user((union chan_val *)arg, &cv, sizeof(union chan_val));
            if (ret)
                return -EFAULT;
            break;
        default:
            return -ENOTTY;
    }

    return 0;
}

static struct file_operations fsadc_ops = {
    .owner = THIS_MODULE,
    .open = fsadc_open,
    .release = fsadc_release,
    .unlocked_ioctl = fsadc_ioctl,
};

static irqreturn_t fsadc_irq_handler(int irq, void *dev_id) {
    struct fsadc_dev *fsadc = dev_id;
    fsadc->adcval = readl(fsadc->adcdat);
    // 清除本次中断，否则无法产生下一次中断
    writel(1, fsadc->adcint);
    complete(&fsadc->completion);

    return IRQ_HANDLED;
}

static int fsadc_probe(struct platform_device *pdev) {
    dev_t dev;
    struct fsadc_dev *fsadc;
    int ret;
    struct resource *res;

    dev = MKDEV(DEV_MA, 0);
    ret = register_chrdev_region(dev, 1, "fsadc");
    if (ret)
        goto err_reg_cdev;

    device_create(fsadc_cls, NULL, dev, NULL, "fsadc");

    fsadc = kzalloc(sizeof(struct fsadc_dev), GFP_KERNEL);
    if (!fsadc) {
        ret = -ENOMEM;
        goto err_mem;
    }

    platform_set_drvdata(pdev, fsadc);

    cdev_init(&fsadc->cdev, &fsadc_ops);
    fsadc->cdev.owner = THIS_MODULE;
    ret = cdev_add(&fsadc->cdev, dev, 1);
    if (ret)
        goto err_add_cdev;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        ret = -ENOENT;
        goto err_res;
    }

    fsadc->adccon = ioremap(res->start, resource_size(res));
    if (!fsadc->adccon) {
        ret = -EBUSY;
        goto err_map;
    }
    fsadc->adcdat = fsadc->adccon + 3;
    fsadc->adcint = fsadc->adccon + 6;
    fsadc->adcmux = fsadc->adccon + 7;

    // 获取中断信息
    fsadc->irq = platform_get_irq(pdev, 0);
    if (fsadc->irq < 0) {
        ret = fsadc->irq;
        goto err_irq;
    }

    // 注册中断处理函数
    ret = request_irq(fsadc->irq, fsadc_irq_handler, 0, "fsadc_interrupt", fsadc);
    if (ret) {
        goto err_irq;
    }

    writel((1<<16) | (1<<14) | (19<<6), fsadc->adccon);

    init_completion(&fsadc->completion);
    printk("-----%s-----\n", __FUNCTION__);

    return 0;

err_irq:
    iounmap(&fsadc->cdev);
err_map:
err_res:
    cdev_del(&fsadc->cdev);
err_add_cdev:
    kfree(fsadc);
err_mem:
    device_destroy(fsadc_cls, dev);
    unregister_chrdev_region(dev, 1);
err_reg_cdev:
    return ret;
}

static int fsadc_remove(struct platform_device *pdev) {
    dev_t dev;
    struct fsadc_dev *fsadc = platform_get_drvdata(pdev);

    dev = MKDEV(DEV_MA, 0);

    writel((readl(fsadc->adccon) & ~(1<<14))|(1<<2), fsadc->adccon);
    free_irq(fsadc->irq, fsadc);
    iounmap(fsadc->adccon);
    cdev_del(&fsadc->cdev);
    kfree(fsadc);
    device_destroy(fsadc_cls, dev);
    unregister_chrdev_region(dev, 1);
    printk("-----%s-----\n", __FUNCTION__);

    return 0;
}

static const struct of_device_id fsadc_of_matches[] = {
    { .compatible = "fs4412, fsadc", },
    {},
};

MODULE_DEVICE_TABLE(of, fsadc_of_matches);

static struct platform_driver fsadc_drv = {
    .driver = {
        .name = "fsadc",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fsadc_of_matches),
    },
    .probe = fsadc_probe,
    .remove = fsadc_remove,
};

static int __init fsadc_init(void) {
    fsadc_cls = class_create(THIS_MODULE, "fsadc");
    platform_driver_register(&fsadc_drv);
    printk("-----%s-----\n", __FUNCTION__);

    return 0;
}

static void __exit fsadc_exit(void) {
    platform_driver_unregister(&fsadc_drv);
    class_destroy(fsadc_cls);
    printk("-----%s-----\n", __FUNCTION__);
}

module_init(fsadc_init);
module_exit(fsadc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ruj");