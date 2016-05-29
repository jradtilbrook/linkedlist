# PROJECT:	Linked list library
# AUTHOR:	Jarryd Tilbrook
# DATE:		24 May 2016
# Main makefile to build the library and the tests

CC = gcc
CFLAGS = -Wall -pedantic
C89 = -ansi
SOURCE = linkedlist.c
OBJECT = $(SOURCE:%.c=%.o)
TEST_BIN = test/unittests

# build everything
all: build buildtests

# build the library
build: $(OBJECT)

$(OBJECT): $(SOURCE) $(SOURCE:%.c=%.h)
	@echo "Compiling library..."
	$(CC) $(CFLAGS) $(C89) -c $(SOURCE)
	@echo "Done."

# build the unit tests
buildtests: $(TEST_BIN)

$(TEST_BIN): $(SOURCE) $(SOURCE:%.c=%.h) test/unittests.c
	@cd test && make

# run the tests
test:
	@cd test && make test

# build documentation for hosting
docs:
	@echo "This still needs to be done."

# clean everything
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJECT)
	@echo "Cleaning binary files..."
	@rm -f $(TEST_BIN)
	@echo "Done."

.PHONY: all build buildtests test docs clean
