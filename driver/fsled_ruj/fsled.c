#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/platform_device.h>

#include "fsled.h"

#define DEV_MA (222)

struct class *fsled_cls;

struct fsled_dev {
	unsigned int __iomem *gpiocon;
	unsigned int __iomem *gpiodat;
	unsigned int pin;
	struct cdev cdev;
};

static int fsled_open(struct inode *inode, struct file *filp) {
	struct fsled_dev *fsled = container_of(inode->i_cdev, struct fsled_dev, cdev);
	filp->private_data = fsled;

	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

static int fsled_release(struct inode *inode, struct file *filp) {
	struct fsled_dev *fsled = filp->private_data;
	writel(readl(fsled->gpiodat) & ~(0x1<<fsled->pin), fsled->gpiodat);

	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

static long fsled_ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	struct fsled_dev *fsled = filp->private_data;

	if (_IOC_TYPE(cmd) != FSLED_MAGIC)
		return -ENOTTY;

	switch (cmd) {
	case FSLED_ON:
		writel(readl(fsled->gpiodat) | 0x1<<fsled->pin, fsled->gpiodat);
		break;
	case FSLED_OFF:
		writel(readl(fsled->gpiodat) & ~(0x1<<fsled->pin), fsled->gpiodat);
		break;
	}

	return 0;
}

struct file_operations fsled_ops = {
	.owner = THIS_MODULE,
	.open = fsled_open,
	.release = fsled_release,
	.unlocked_ioctl = fsled_ioctl,
};

static int fsled_probe(struct platform_device *pdev) {
	dev_t dev;
	int ret = 0;
	struct fsled_dev *fsled;
	struct resource *res;

	// 注册设备号
	of_property_read_u32(pdev->dev.of_node, "id", &pdev->id);
	dev = MKDEV(DEV_MA, pdev->id);
	ret = register_chrdev_region(dev, 1, "fsled");
	if (ret)
		goto err_reg;

	// 创建设备文件
	device_create(fsled_cls, NULL, dev, NULL, "led%d", pdev->id);

	// 申请设备指针空间
	fsled = kzalloc(sizeof(struct fsled_dev), GFP_KERNEL);
	if (!fsled) {
		ret = -ENOMEM;
		goto err_mem;
	}

	// 初始化、添加字符设备
	cdev_init(&fsled->cdev, &fsled_ops);
	fsled->cdev.owner = THIS_MODULE;
	ret = cdev_add(&fsled->cdev, dev, 1);
	if (ret)
		goto err_add;

	// 获取设备资源
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		ret = -ENOENT;
		goto err_res;
	}
	fsled->gpiocon = ioremap(res->start, resource_size(res));
	if (!fsled->gpiocon) {
		ret = -EBUSY;
		goto err_remap;
	}
	fsled->gpiodat = fsled->gpiocon + 1;
	of_property_read_u32(pdev->dev.of_node, "pin", &fsled->pin);

	// 初始化led设备
	writel((readl(fsled->gpiocon) & ~(0xf<<4*fsled->pin)) | (0x1<<4*fsled->pin), fsled->gpiocon);
	writel(readl(fsled->gpiodat) & ~(0x1<<fsled->pin), fsled->gpiodat);

	// 将fsled存入pdev的drvdata中，在remove函数中可以取出使用
	platform_set_drvdata(pdev, fsled);

	printk("-----%s-----\n", __FUNCTION__);

	return 0;
err_remap:
err_res:
	cdev_del(&fsled->cdev);
err_add:
	kfree(fsled);
err_mem:
	unregister_chrdev_region(dev, 1);
err_reg:
	return ret;
}

static int fsled_remove(struct platform_device *pdev) {
	dev_t dev;
	struct fsled_dev *fsled = platform_get_drvdata(pdev);
	dev = MKDEV(DEV_MA, pdev->id);

	iounmap(fsled->gpiocon);
	cdev_del(&fsled->cdev);
	kfree(fsled);
	device_destroy(fsled_cls, dev);
	unregister_chrdev_region(dev, 1);

	printk("-----%s-----\n", __FUNCTION__);

	return 0;
}

static const struct of_device_id fsled_of_matches[] = {
	{ .compatible = "fs4412, fsled", },
	{ /*sentinel*/ },
};

MODULE_DEVICE_TABLE(of, fsled_of_matches);

static struct platform_driver fsled_drv = {
	.driver = {
		.name = "fsled",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(fsled_of_matches),
	},
	.probe = fsled_probe,
	.remove = fsled_remove,
};

static int __init fsled_init(void) {
	fsled_cls = class_create(THIS_MODULE, "fsled");
	platform_driver_register(&fsled_drv);

	return 0;
}

static void __exit fsled_exit(void) {
	platform_driver_unregister(&fsled_drv);
	class_destroy(fsled_cls);
}

module_init(fsled_init);
module_exit(fsled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ruj");
