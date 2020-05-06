#include <linux/module.h>
#include <linux/init.h>
#include "math.h"

static int myvalue = 555;
static char *myname = "ruj";

static int __init hello_drv_init(void) {
    printk("-----%s-----\n", __FUNCTION__);
    printk("name = %s, value = %d\n", myname, myvalue);
    printk("add = %d, sub = %d\n", my_add(10, 20), my_sub(33, 22));
    return 0;
}

static void __exit hello_drv_exit(void) {
    printk("-----%s-----\n", __FUNCTION__);
    return ;
}

module_init(hello_drv_init);
module_exit(hello_drv_exit);
MODULE_LICENSE("GPL");
module_param(myvalue, int, 0644);
module_param(myname, charp, S_IRUGO | S_IWUSR);