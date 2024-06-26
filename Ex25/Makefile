CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex25.exe
SRC = ex25.c

.PHONY: all clean test

all: ex25

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET)