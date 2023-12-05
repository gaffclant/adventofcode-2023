TARGET = solution
BIN = bin
SRC = src
CC = clang
WARNINGS = -Wall -Werror -Wextra
CFLAGS = 

.PHONY: all
all: $(BIN)/$(TARGET)1 $(BIN)/$(TARGET)2

$(BIN)/$(TARGET)1:
	mkdir -p bin
	$(CC) $(WARNINGS) $(CFLAGS) $(SRC)/part1.c -o $@

$(BIN)/$(TARGET)2:
	mkdir -p bin
	$(CC) $(WARNINGS) $(CFLAGS) $(SRC)/part2.c -o $@

.PHONY: clean
clean:
	rm -rf bin/
