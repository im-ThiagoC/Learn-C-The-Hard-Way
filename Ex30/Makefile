CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex30.exe
SRC = ex30.c

.PHONY: all clean test

all: ex30

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)