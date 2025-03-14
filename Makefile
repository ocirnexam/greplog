CFLAGS=-Wall
BUILDDIR := build
DEBUGDIR := debug

SRCS := $(shell find src -name '*.c')

main: src/main.c
	mkdir -p $(BUILDDIR)
	gcc $(CFLAGS) -o $(BUILDDIR)/logfind $(SRCS)

debug: src/main.c
	mkdir -p $(DEBUGDIR)
	gcc $(CFLAGS) -g -o $(DEBUGDIR)/logfind $(SRCS)

clean:
	rm -r $(BUILDDIR)
	rm -r $(DEBUGDIR)
