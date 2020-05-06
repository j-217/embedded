ROOTFS_DIR = /home/vem/rootfs

ifeq ($(KERNELRELEASE), )
	KERNEL_DIR = /home/vem/linux-3.14
	CUR_DIR = $(shell pwd)

all:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) modules

clean:
	make -C $(KERNEL_DIR) M=$(CUR_DIR) clean

install:
	cp -raf *.ko $(ROOTFS_DIR)/drv_module

else
	obj-m += hello_drv.o
	obj-m += math.o
endif

