.OBJECTS=$(wildcard src/*.c)
OBJECTS = $(.OBJECTS:src%.c=obj%.o)
CC=clang
CFLAGS=-std=c11 -Wall -Wextra -Werror
NAME=pathfinder
LIBMX_MAKE=$(MAKE) -C libmx

all: clean prepare $(NAME)

prepare:
	mkdir -p obj/
	$(LIBMX_MAKE)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) obj/*.o libmx/libmx.a

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

clean:
	rm -rf obj
	$(LIBMX_MAKE) clean

uninstall: clean
	rm -f $(NAME)
	$(LIBMX_MAKE) uninstall

reinstall: uninstall all

run: all
	./$(NAME)
