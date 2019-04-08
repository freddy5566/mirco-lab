obj-m := lab5.o
kernel_DIR := /usr/src/linux-headers-4.4.0-93-generic
PWD := $(shell pwd)
all:
	make -C $(kernel_DIR) SUBDIRS=$(PWD)
clean:
	rm *.o *.ko *.mod.c
.PHONY:clean


