#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

static unsigned int dev_major = 250;
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
	class_create(owner, name);
	device_create(struct class * class, struct device * parent, dev_t devt, void * drvdata, const char * fmt, ...);

	return 0;
}

static void __exit chr_dev_exit(void) {
	unregister_chrdev(dev_major, "chr_dev_test");
	return ;
}

module_init(chr_dev_init);
module_exit(chr_dev_exit);
MODULE_LICENSE("GPL");
