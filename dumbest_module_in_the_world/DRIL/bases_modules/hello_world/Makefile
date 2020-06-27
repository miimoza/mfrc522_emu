KDIR := /usr/src/linux-headers-$(shell uname -r)
PWD  := $(shell pwd)

MODULE_NAME := basic

obj-m := basic_main.o

all:
	make -C "$(KDIR)" SUBDIRS="$(PWD)" modules

install:
	make -C "$(KDIR)" SUBDIRS="$(PWD)" modules_install

clean:
	make -C "$(KDIR)" SUBDIRS="$(PWD)" clea_n
