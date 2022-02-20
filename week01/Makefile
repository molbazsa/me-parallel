CC = gcc
CFLAGS = -std=c11 -pedantic -Wall

SRC = src
OBJ = obj
BIN = bin
EXT = .exe

TARGETS = ex04random ex05random ex06sum

all: $(foreach target, $(TARGETS), $(BIN)/$(target)$(EXT))

$(BIN)/ex04random$(EXT): $(SRC)/ex04random.c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/ex05random$(EXT): $(SRC)/ex05random.c
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/ex06sum$(EXT): $(SRC)/ex06sum.c
	$(CC) $(CFLAGS) $^ -o $@

DIRS = $(OBJ) $(BIN)

dirs:
	mkdir $(DIRS)
