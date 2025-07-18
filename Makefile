all: output

CC ?= gcc
CFLAGS ?= -Iinclude -std=c17 -Wall -Wextra -pedantic -Werror

.PHONY: clean
clean:
	rm -rf output

obj:
	mkdir -p obj

output: obj/main.o obj/str.o
	$(CC) $(LDFLAGS) $^ -o $@

obj/main.o: src/main.c include/str.h | obj
	$(CC) -c $(CFLAGS) $< -o $@

obj/str.o: src/str.c include/str.h | obj
	$(CC) -c $(CFLAGS) $< -o $@
