
PROGS=rect

LFLAGS=-lpmemobj -lpmem -pthread
CC=g++
CFLAGS= -O3 -g

all: rect 
rect: main.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)


clean:
	rm rect 
