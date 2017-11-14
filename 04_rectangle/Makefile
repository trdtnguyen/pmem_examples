
PROGS=rect

LFLAGS=-lpmemobj -lpmem -pthread
CC=g++
CFLAGS= -O3 -g

all: rect reader persistent_test
rect: main.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)
reader: reader.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)

persistent_test: persistent_test.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)
clean:
	rm rect reader persistent_test
