#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/ioctl.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

#include "fsrtc.h"

struct fsrtc_dev {
    struct cdev cdev;

    unsigned int __iomem *rtcbase;
    unsigned int __iomem *rtccon;
    unsigned int __iomem *bcdsec;
    unsigned int __iomem *bcdmin;
    unsigned int __iomem *bcdhour;
    unsigned int __iomem *bcdday;
    unsigned int __iomem *bcdmon;
    unsigned int __iomem *bcdyear;

    struct clk *clk;
    unsigned long freq;
}__attribute__((packed));

static int fsrtc_open(struct inode *inode, struct file *filp) {
    struct fsrtc_dev *fsrtc = container_of(inode->i_cdev, struct fsrtc_dev, cdev);
    filp->private_data = fsrtc;

    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static int fsrtc_release(struct inode *inode, struct file *filp) {
    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static long fsrtc_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
    struct fsrtc_dev *fsrtc = filp->private_data;
    struct rtc_time tm;
    int ret;

    if (_IOC_TYPE(cmd) != FSRTC_MAGIC)
        return -ENOTTY;

    switch (cmd) {
        case FSRTC_SET:
            ret = copy_from_user(&tm, (struct rtc_time *)arg, sizeof(struct rtc_time));
            if (ret)
                return -ENOTTY;

            writel(readl(fsrtc->rtccon) | 0x1, fsrtc->rtccon);
            writel(tm.tm_sec, fsrtc->bcdsec);
            writel(tm.tm_min, fsrtc->bcdmin);
            writel(tm.tm_hour, fsrtc->bcdhour);
            writel(tm.tm_day, fsrtc->bcdday);
            writel(tm.tm_mon, fsrtc->bcdmon);
            writel(tm.tm_year, fsrtc->bcdyear);
            writel(readl(fsrtc->rtccon) & ~0x1, fsrtc->rtccon);
            break;
        case FSRTC_GET:
            tm.tm_sec = readl(fsrtc->bcdsec);
            tm.tm_min = readl(fsrtc->bcdmin);
            tm.tm_hour = readl(fsrtc->bcdhour);
            tm.tm_day = readl(fsrtc->bcdday);
            tm.tm_mon = readl(fsrtc->bcdmon);
            tm.tm_year = readl(fsrtc->bcdyear);

            ret = copy_to_user((struct rtc_time *)arg, &tm, sizeof(struct rtc_time));
            if (ret)
                return -ENOTTY;

            break;
        default:
            return -ENOTTY;
    }

    printk("-----%s-----\n", __FUNCTION__);
    return 0;
}

static struct file_operations fsrtc_ops = {
    .owner = THIS_MODULE,
    .open = fsrtc_open,
    .release = fsrtc_release,
    .unlocked_ioctl = fsrtc_ioctl,
};

static int fsrtc_probe(struct platform_device *pdev) {
    dev_t dev;
    int ret;
    struct fsrtc_dev *fsrtc;
    struct resource *res;

    dev = MKDEV(2222, 0);
    ret = register_chrdev_region(dev, 1, "fsrtc");
    if (ret)
        goto err_reg;

    fsrtc = kzalloc(sizeof(struct fsrtc_dev), GFP_KERNEL);
    if (!fsrtc) {
        ret = -ENOMEM;
        goto err_mem;
    }

    platform_set_drvdata(pdev, fsrtc);

    cdev_init(&fsrtc->cdev, &fsrtc_ops);
    fsrtc->cdev.owner = THIS_MODULE;
    ret = cdev_add(&fsrtc->cdev, dev, 1);
    if (ret)
        goto err_add_cdev;

    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        ret = -ENOENT;
        goto err_res;
    }

    fsrtc->rtcbase = ioremap(res->start, resource_size(res));
    if (!fsrtc->rtcbase) {
        ret = -EBUSY;
        goto err_map;
    }

    fsrtc->rtccon = fsrtc->rtcbase + 0x10;
    fsrtc->bcdsec = fsrtc->rtcbase + 0x1c;
    fsrtc->bcdmin = fsrtc->rtcbase + 0x1d;
    fsrtc->bcdhour = fsrtc->rtcbase + 0x1e;
    fsrtc->bcdday = fsrtc->rtcbase + 0x20;
    fsrtc->bcdmon = fsrtc->rtcbase + 0x21;
    fsrtc->bcdyear = fsrtc->rtcbase + 0x22;

    fsrtc->clk = clk_get(&pdev->dev, "rtc");
    if (IS_ERR(fsrtc->clk)) {
        ret = PTR_ERR(fsrtc->clk);
        goto err_clk;
    }

    ret = clk_prepare_enable(fsrtc->clk);
    if (ret)
        goto err_enable_clk;

    fsrtc->freq = clk_get_rate(fsrtc->clk);
    printk("freq: %lu\n", fsrtc->freq);

    printk("-----%s-----\n", __FUNCTION__);

    return 0;

err_enable_clk:
    clk_put(fsrtc->clk);
err_clk:
    iounmap(fsrtc->rtcbase);
err_map:
err_res:
    cdev_del(&fsrtc->cdev);
err_add_cdev:
    kfree(fsrtc);
err_mem:
    unregister_chrdev_region(dev, 1);
err_reg:
    return ret;
}

static int fsrtc_remove(struct platform_device *pdev) {
    dev_t dev;
    struct fsrtc_dev *fsrtc = platform_get_drvdata(pdev);

    dev = MKDEV(2222, 0);

    clk_disable_unprepare(fsrtc->clk);
    clk_put(fsrtc->clk);
    iounmap(fsrtc->rtcbase);
    cdev_del(&fsrtc->cdev);
    kfree(fsrtc);
    unregister_chrdev_region(dev, 1);

    printk("-----%s-----\n", __FUNCTION__);

    return 0;
}

static const struct of_device_id fsrtc_of_matches[] = {
    { .compatible = "fs4412, fsrtc", },
    {},
};

MODULE_DEVICE_TABLE(of, fsrtc_of_matches);

static struct platform_driver fsrtc_drv = {
    .driver = {
        .name = "fsrtc",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fsrtc_of_matches),
    },
    .probe = fsrtc_probe,
    .remove = fsrtc_remove,
};

module_platform_driver(fsrtc_drv);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ruj");