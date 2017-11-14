
LFLAGS=-lpmemobj -lpmem -pthread
CC=g++
CFLAGS= -O3 -g

all: doubled_linked_list
doubled_linked_list: doubled_linked_list.c
	$(CC) -o dll $^ $(CFLAGS) $(LFLAGS)
clean:
	rm dll
