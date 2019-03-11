FILE=main
CFLAGS=-Wall -g
CROSS_COMPILE=arm-linux-gnueabihf
CC= $(CROSS_COMPILE)cc
LIBS=-lm
INCLUDES= 
OBJS=
SRCS=main.cpp

all: $(FILE) 
$(FILE): $(FILE).o $(OBJS)	
				$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(FILE).o $(OBJS) $(LIBS)
clean:
			rm *.o $(FILE)
