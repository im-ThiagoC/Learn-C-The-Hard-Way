CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex27.exe
SRC = ex27.c

.PHONY: all clean test

all: ex27

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)