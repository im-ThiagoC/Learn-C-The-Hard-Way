CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
TARGET = ex19.exe
SRC = ex19.c

.PHONY: all clean test

all: ex19

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

%.exe: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(TARGET)

test: $(TARGET)
	./$(TARGET) db.dat c
	./$(TARGET) db.dat s 1 tHIago thiago@com
	./$(TARGET) db.dat s 2 MARIA MARIA@COM
	./$(TARGET) db.dat s 3 thiagooos thhh@com
	./$(TARGET) db.dat g 1
	./$(TARGET) db.dat g 2
	./$(TARGET) db.dat l
	./$(TARGET) db.dat n thiago
	./$(TARGET) db.dat e thiago
