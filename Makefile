CFLAGS=-Wall -g

all:
	gcc -o logfind $(CFLAGS) src/main.c

clean:
	rm -f logfind
