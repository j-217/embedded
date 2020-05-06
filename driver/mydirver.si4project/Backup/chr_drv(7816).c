#include <linux/init.h>
#include <linux/module.h>
#include <fs.h>
#include <linux/device.h>

static unsigned int dev_major = 250;
static struct class *dev_cls;
static struct device *dev;

ssize_t chr_dev_read (struct file *flip, char __user * buf, size_t count, loff_t *fpos) {
	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

ssize_t chr_dev_write (struct file *flip, const char __user * buf, size_t count, loff_t *fpos) {
	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

int chr_dev_open (struct inode *inod, struct file *filp) {
	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

int chr_dev_close (struct inode *inod, struct file *filp) {
	printk("-----%s-----\n", __FUNCTION__);
	return 0;
}

const struct file_operations my_fops = {
	.open = chr_dev_open,
	.read = chr_dev_read,
	.write = chr_dev_write,
	.release = chr_dev_close,
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
	device_destroy(dev_cls, MKDEV(dev_major, 0));
	class_destroy(dev_cls);
	unregister_chrdev(dev_major, "chr_dev_test");
	return ;
}

module_init(chr_dev_init);
module_exit(chr_dev_exit);
MODULE_LICENSE("GPL");
