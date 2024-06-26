CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex24.exe
SRC = ex24.c

.PHONY: all clean test

all: ex24

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)