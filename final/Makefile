obj-m := led1.o led2.o led3.o led4.o
KERNEL_DIR := /usr/src/kernel
PWD := $(shell pwd)
all:
	g++ -I/usr/local/include/opencv -I/usr/local/include/opencv2 -L/usr/local/lib/ -g -o OutputProgrameName test.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_stitching
	make -C $(KERNEL_DIR) SUBDIRS=$(PWD)
clean:
#clean
	rm -f OutputProgrameName *.jpg *.o *.ko *.mod.c

.PHONY:
	clean
