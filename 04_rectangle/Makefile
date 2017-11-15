
PROGS=rect

LFLAGS=-lpmemobj -lpmem -pthread
CC=g++
CFLAGS= -g

all: rect reader persistent_test test_nolib reader_nolib
rect: main.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)
reader: reader.c
	$(CC)	-o $@ $^ $(CFLAGS) $(LFLAGS)

persistent_test: persistent_test.c
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
test_nolib: test_nolib.c
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

reader_nolib: reader_nolib.c
	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)

clean:
	rm rect reader persistent_test test_nolib reader_nolib
