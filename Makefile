CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

TARGET = minesweeper

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

mem-test: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)