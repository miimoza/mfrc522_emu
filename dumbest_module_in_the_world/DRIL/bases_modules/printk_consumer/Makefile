KDIR = /usr/src/linux-headers-$(shell uname -r)
PWD  = $(shell pwd)

obj-m = consumer.o

all:
	#make -C $(KDIR) SUBDIRS=$(PWD) KBUILD_EXTRA_SYMBOLS=$(PWD)/../printk/Module.symvers modules
	make -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	make -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
