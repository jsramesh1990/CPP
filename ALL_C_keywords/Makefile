# C Keyword Mastery Project Makefile
# Note: Use TABS for indentation, not spaces!

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g
TARGET = c_keyword_demo
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC_DIR)/main.c $(SRC_DIR)/c_keywords_demo.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@
	@echo "Build successful! Run with: make run"

clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build files"

run: all
	@echo "Running C Keyword Mastery Program..."
	@echo "========================================"
	./$(BUILD_DIR)/$(TARGET)

test: all
	@echo "Running program..."
	./$(BUILD_DIR)/$(TARGET)

help:
	@echo "Available commands:"
	@echo "  make           - Build the program"
	@echo "  make clean     - Remove build files"
	@echo "  make run       - Build and run program"
	@echo "  make test      - Build and run (alias for run)"
	@echo "  make help      - Show this help"

.PHONY: all clean run test help
