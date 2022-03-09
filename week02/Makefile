CC = gcc
INCLUDES = -Iinclude
CFLAGS = -g -std=c11 -pedantic -Wall $(INCLUDES)

TARGETS = gen_array ex01prefix
EXT = .exe

all: $(foreach target, $(TARGETS), bin/$(target)$(EXT))


bin/gen_array$(EXT): obj/gen_array.o obj/array_export.o
	$(CC) $(CFLAGS) $^ -o $@

obj/gen_array.o: src/gen_array.c include/array_export.h
	$(CC) -c $(CFLAGS) $< -o $@


bin/ex01prefix$(EXT): obj/ex01prefix.o obj/array_export.o
	$(CC) $(CFLAGS) $^ -o $@

obj/ex01prefix.o: src/ex01prefix.c include/array_export.h include/perf_timing.h
	$(CC) -c $(CFLAGS) $< -o $@


obj/array_export.o: src/array_export.c include/array_export.h
	$(CC) -c $(CFLAGS) $< -o $@


dirs:
	mkdir data obj bin
