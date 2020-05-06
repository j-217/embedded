#include <linux/module.h>
#include <linux/init.h>

int my_add(int a, int b) {
    return a + b;
}

int my_sub(int a, int b) {
    return a - b;
}

EXPORT_SYMBOL(my_add);
EXPORT_SYMBOL(my_sub);
MODULE_LICENSE("GPL");