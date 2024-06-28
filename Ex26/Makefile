CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = logfind.exe
SRC = logfind.c

.PHONY: all clean test

all: logfind

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)