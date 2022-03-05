CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Iinclude

TARGETS = gen_array ex01prefix
EXT = .exe

all: $(foreach target, $(TARGETS), bin/$(target)$(EXT))

bin/gen_array$(EXT): src/gen_array.c obj/array_export.o
	$(CC) $(CFLAGS) $^ -o $@

obj/array_export.o: src/array_export.c include/array_export.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/ex01prefix$(EXT): src/ex01prefix.c
	$(CC) $(CFLAGS) $^ -o $@

dirs:
	mkdir data obj bin
