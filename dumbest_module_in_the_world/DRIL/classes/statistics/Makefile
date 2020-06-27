KDIR ?= /usr/src/linux-headers-$(shell uname -r)
PWD  := $(shell pwd)

obj-m := statistics.o

modules modules_install clean:
	make -C $(KDIR) SUBDIRS=$(PWD) $@
