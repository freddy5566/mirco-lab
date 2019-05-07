FILE=week8
CFLAGS=-Wall -g
CROSS_COMPILE=arm-linux-gnueabihf-
CC= $(CROSS_COMPILE)g++
LIBS=-lm
INCLUDES= 
OBJS=
SRCS=week8.cpp

all: $(FILE) 
	$(CC) $(CFLAGS) $(SRCS)
clean:
	rm *.o $(FILE)
