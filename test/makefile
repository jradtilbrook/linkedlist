# AUTHOR:	Jarryd Tilbrook
# DATE:		24 May 2016
# Makefile to build unit tests for linked list library.

CC = gcc
CFLAGS = -Wall -pedantic -g
CMOCKA = `pkg-config --libs --cflags cmocka`
BIN = unittests

# build the unit tests
build: $(BIN)

$(BIN): unittests.c ../linkedlist.c ../linkedlist.h
	@echo "Compiling unit tests..."
	$(CC) $(CFLAGS) -D UNIT_TESTING unittests.c ../linkedlist.c -o $(BIN) $(CMOCKA)
	@echo "Done."

# run the tests
test: build
	@./$(BIN)

# clean the binary
clean:
	@echo "Cleaning unit tests..."
	@rm -f $(BIN)
	@echo "Done."

.PHONY: build test clean
