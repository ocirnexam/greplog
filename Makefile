CFLAGS=-Wall -g

all:
	gcc -o logfind $(CFLAGS) src/main.c
