# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -DNDEBUG
LDFLAGS = -ljson-c -lmosquitto
TARGET = mosquitto-test
SRC = mosquitto-test.c
JSON_FILE = mosquitto-test.json

# Regras
.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(JSON_FILE)

test: $(TARGET)
	./$(TARGET)
