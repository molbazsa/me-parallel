CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall
INCLUDES = -Iinclude
FLAGS = $(CFLAGS) $(INCLUDES)
LDFLAGS = -pthread

TARGETS = posix01 posix02 ex01sum
EXT = .exe

all: $(foreach target, $(TARGETS), bin/$(target)$(EXT))

install: dirs
install: all

bin/posix01$(EXT): src/posix01.c
	$(CC) $(FLAGS) $^ -o $@ $(LDFLAGS)

bin/posix02$(EXT): src/posix02.c
	$(CC) $(FLAGS) $^ -o $@ $(LDFLAGS)

dirs:
	mkdir data obj bin
