KERNEL_DIR ?= /home/vem/linux-3.14
PWD := $(shell pwd)
ROOTFS ?= /home/vem/rootfs

ifeq ($(KERNELRELEASE), )
defalut:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules
module_install:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) INSTALL_MOD_PATH=$(ROOTFS) modules_install
clean:
	rm -f *.ko *.o *.mod.* *.order *.symvers *.mod

else
	obj-m := fskey_input.o
endif