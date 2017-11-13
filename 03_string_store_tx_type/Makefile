
PROGS=writer reader

LFLAGS=-lpmemobj -lpmem -pthread
CC=g++
CFLAGS= -O3 -g

all: writer reader
writer: writer.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)

reader: reader.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm *.o writer reader
