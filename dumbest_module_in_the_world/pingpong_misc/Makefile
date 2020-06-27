KDIR ?= /usr/src/linux-headers-$(shell uname -r)
PWD  := $(shell pwd)

obj-m := pingpong_misc.o

modules modules_install clean:
	make -C $(KDIR) SUBDIRS=$(PWD) $@
