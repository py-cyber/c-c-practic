CC ?= gcc
CFLAGS ?= -Iinclude -std=c17 -Wall -Wextra -pedantic -Werror
LDFLAGS ?=

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = output

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(EXECUTABLE) $(OBJ_DIR)
