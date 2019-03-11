FILE=main
CFLAGS=-Wall -g 
CC=gcc
LIBS=-lm
INCLUDES= 
OBJS=sort.o
SRCS=main.cpp sort.cpp


all: $(FILE) 
$(FILE): $(FILE).o $(OBJS)	
				$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(FILE).o $(OBJS) $(LIBS)
clean:
			rm *.o $(FILE)
