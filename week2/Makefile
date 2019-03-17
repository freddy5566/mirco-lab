FILE=main
CFLAGS=-Wall -g
CROSS_COMPILE=arm-linux-gnueabihf-
CC= $(CROSS_COMPILE)g++
LIBS=-lm
INCLUDES= 
OBJS=
SRCS=main.cpp

all: $(FILE) 
	$(CC) $(CFLAGS) $(SRCS)
clean:
	rm *.o $(FILE)
