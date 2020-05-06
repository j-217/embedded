#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/input.h>
#include <linux/input-polldev.h>
#include <linux/platform_device.h>

#define MAX_KEYS_NUM (8)
#define SCAN_INTERVAL (50)
#define KB_ACTIVATE_DELAY (20)
#define KB_SCAN_STABLE_COUNT (3)

struct fskey_dev {
    struct input_polled_dev *polldev;
    unsigned int count;
    unsigned int kstate[MAX_KEYS_NUM];
    unsigned int kcount[MAX_KEYS_NUM];
    unsigned char keycode[MAX_KEYS_NUM];
    int gpio[MAX_KEYS_NUM];
};

static void fskey_poll_handler(struct input_polled_dev *dev)
{
    unsigned int i;
    unsigned int kstate;
    struct fskey_dev *fskey = dev->private;

    for (i = 0; i < fskey->count; ++i) {
        fskey->kcount[i] = 0;
    }

    i = 0;
    do {
        udelay(KB_ACTIVATE_DELAY);
        kstate = gpio_get_value(fskey->gpio[i]);
        if (kstate != fskey->kstate[i]) {
            fskey->kstate[i] = kstate;
            fskey->kcount[i] = 0;
        } else {
            if (++fskey->kcount[i] >= KB_SCAN_STABLE_COUNT) {
                input_report_key(dev->input, fskey->keycode[i], !kstate);
                ++i;
            }
        }
    } while (i < fskey->count);

    input_sync(dev->input);
}

static int fskey_probe(struct platform_device *pdev)
{
    int ret = 0;
    int i;
    struct fskey_dev *fskey;

    fskey = kzalloc(sizeof(struct fskey_dev), GFP_KERNEL);
    if (!fskey) {
        ret = -ENOMEM;
        goto err_alloc;
    }

    platform_set_drvdata(pdev, fskey);

    fskey->count = 0;
    for (i = 0; i < MAX_KEYS_NUM; ++i) {
        ret = of_get_gpio(pdev->dev.of_node, i);
        if (ret < 0) {
            continue;
        } else {
            fskey->gpio[i] = ret;
            ++fskey->count;
        }
    }
    if (i == 0) {
        goto err_gpio;
    }

    for (i = 0; i < fskey->count; ++i) {
        ret = gpio_request(fskey->gpio[i], "KEY");
        if (ret)
            goto err_req_gpio;

        gpio_direction_input(fskey->gpio[i]);
        fskey->keycode[i] = KEY_2 + i;
        fskey->kstate[i] = 1;
    }

    fskey->polldev = input_allocate_polled_device();
    if (!fskey->polldev) {
        ret = -ENOMEM;
        goto err_req_gpio;
    }

    fskey->polldev->private = fskey;
    fskey->polldev->poll = fskey_poll_handler;
    fskey->polldev->poll_interval = SCAN_INTERVAL;

    fskey->polldev->input->name = "FS4412 Keyboard";
    fskey->polldev->input->phys = "input0";
    fskey->polldev->input->id.bustype = BUS_HOST;
    fskey->polldev->input->id.product = 0x0001;
    fskey->polldev->input->id.vendor = 0x0002;
    fskey->polldev->input->id.version = 0x0010;
    fskey->polldev->input->dev.parent = &pdev->dev;

    fskey->polldev->input->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
    fskey->polldev->input->keycode = fskey->keycode;
    fskey->polldev->input->keycodesize = sizeof(unsigned char);
    fskey->polldev->input->keycodemax = i;

    for (i = 0; i < fskey->count; ++i) {
        __set_bit(fskey->keycode[i], fskey->polldev->input->keybit);
    }
    __clear_bit(KEY_RESERVED, fskey->polldev->input->keybit);

    ret = input_register_polled_device(fskey->polldev);
    if (ret) {
        goto err_reg_poll;
    }

    printk("-----%s-----\n", __FUNCTION__);

    return 0;
err_reg_poll:
    input_free_polled_device(fskey->polldev);
err_req_gpio:
    for (--i; i >= 0; --i) {
        gpio_free(fskey->gpio[i]);
    }
err_gpio:
    kfree(fskey);
err_alloc:
    return ret;
}

static int fskey_remove(struct platform_device *pdev)
{
    unsigned int i;
    struct fskey_dev *fskey = platform_get_drvdata(pdev);

    input_unregister_polled_device(fskey->polldev);
    input_free_polled_device(fskey->polldev);
    for (i = 0; i < fskey->count; ++i) {
        gpio_free(fskey->gpio[i]);
    }
    kfree(fskey);
    printk("-----%s-----\n", __FUNCTION__);

    return 0;
}

static const struct of_device_id fskey_of_matches[] = {
    { .compatible = "fs4412, fskey", },
    {},
};

MODULE_DEVICE_TABLE(of, fskey_of_matches);

struct platform_driver fskey_drv = {
    .driver = {
        .name = "fskey",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fskey_of_matches),
    },
    .probe = fskey_probe,
    .remove = fskey_remove,
};

module_platform_driver(fskey_drv);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ruj");