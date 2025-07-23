CC ?= gcc
CFLAGS ?= -Iinclude -std=c17 -Wall -Wextra -pedantic -Werror
LDFLAGS ?=

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
TEST_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = output

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS)) \
               $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SOURCES))
TEST_TARGET = test_runner

.PHONY: all test clean

all: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(TARGET) $(TEST_TARGET) $(OBJ_DIR)
