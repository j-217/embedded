#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>

static unsigned int dev_major = 250;
static struct class *dev_cls;
static struct device *dev;
const struct file_operations my_fops = {

};

static int __init chr_dev_init(void) {
	int ret;
	ret = register_chrdev(dev_major, "chr_dev_test", &my_fops);
	if (ret == 0) {
		printk("register ok\n");
	} else {
		printk("register failed\n");
		return -EINVAL;
	}
	dev_cls = class_create(THIS_MODULE, "chr_cls");
	dev = device_create(dev_cls, NULL, MKDEV(dev_major, 0), NULL, "chr2");

	return 0;
}

static void __exit chr_dev_exit(void) {
	device_destroy(dev_cls, dev);
	class_destroy(dev_cls);
	unregister_chrdev(dev_major, "chr_dev_test");
	return ;
}

module_init(chr_dev_init);
module_exit(chr_dev_exit);
MODULE_LICENSE("GPL");
