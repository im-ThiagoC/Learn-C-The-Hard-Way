CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = logfindv2.exe
SRC = logfindv2.c

.PHONY: all clean test

all: logfindv2

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)