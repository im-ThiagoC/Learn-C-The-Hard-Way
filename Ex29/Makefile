CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex29.exe
SRC = ex29.c

.PHONY: all clean test

all: ex29

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)