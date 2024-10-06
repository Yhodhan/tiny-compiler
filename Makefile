.PHONY: compile
CFLAGS = -g -Wall -Wformat -Werror -Wextra -Wuninitialized -Winit-self -Wmaybe-uninitialized

CC = gcc
SRCS = $(wildcard *.c) $(wildcard */*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

TARGET = compiler

compile: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm  **/*.o *.o
	rm compiler 
	rm emit.c
