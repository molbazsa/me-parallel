CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
INCLUDES = -Iinclude
FLAGS = $(CFLAGS) $(INCLUDES)
LDFLAGS =

TARGETS = array_demo stack_demo
EXT = .exe

all: $(foreach target, $(TARGETS), bin/$(target)$(EXT))

install: dirs
install: all


bin/array_demo$(EXT): obj/array_demo.o obj/array.o
	$(CC) $(FLAGS) $^ -o $@

obj/array_demo.o: src/array_demo.c include/array.h
	$(CC) -c $(FLAGS) $< -o $@

obj/array.o: src/array.c include/array.h
	$(CC) -c $(FLAGS) $< -o $@


bin/stack_demo$(EXT): obj/stack_demo.o obj/array.o obj/stack.o
	$(CC) $(FLAGS) $^ -o $@

obj/stack_demo.o: src/stack_demo.c include/stack.h
	$(CC) -c $(FLAGS) $< -o $@

obj/stack.o: src/stack.c include/array.h include/stack.h
	$(CC) -c $(FLAGS) $< -o $@


dirs:
	mkdir obj bin
