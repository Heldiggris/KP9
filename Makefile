CC = gcc
CFLAGS = -g -std=c99 -Wno-unused-result -pipe -O3

all:  main

main: main.o sort.o
	$(CC) $^ -o $@

generate: generate.o
	$(CC) $^ -o $@

clean:
	rm -f main generate *.o