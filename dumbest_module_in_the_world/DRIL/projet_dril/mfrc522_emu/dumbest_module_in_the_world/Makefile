KDIR := /usr/src/linux-headers-$(shell uname -r)
PWD  := $(shell pwd)

obj-m := dumbest.o

default: modules
modules modules_install clean:
	make -C "$(KDIR)" SUBDIRS="$(PWD)" "$@"
