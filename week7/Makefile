obj-m := demo.o
KERNEL_DIR := /usr/src/linux-headers-4.4.0-93-generic/
PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD)
	gcc write.c -o write.o
	gcc read.c -o read.o
clean:
	rm *.o *.ko *.mod.c
.PHONY:clean

