CC ?= arm-linux-gnueabi-gcc
CFLAGS := --std=c90

SRC  := hello.c
BIN  := init
CPIO := my_initramfs.cpio

all:
	${CC} ${CFLAGS} ${SRC} -static -o ${BIN}
	echo ${BIN} | cpio -o --format=newc > ${CPIO}
