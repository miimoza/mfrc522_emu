KDIR ?= /usr/src/linux-headers-$(shell uname -r)
PWD  := $(shell pwd)

obj-m := dump_on_ioctl.o

USERPROG := userprog

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc -Wall -Wextra -std=c99 userprog.c -o $(USERPROG)

install:
	make -C $(KDIR) SUBDIRS=$(PWD) modules_install

clean:
	make -C $(KDIR) SUBDIRS=$(PWD) clean
	rm $(USERPROG)
