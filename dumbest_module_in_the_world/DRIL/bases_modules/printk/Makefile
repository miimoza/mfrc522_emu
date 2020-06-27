KDIR = /usr/src/linux-headers-$(shell uname -r)
PWD  = $(shell pwd)

obj-m = my_printk.o

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

install:
	make -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
