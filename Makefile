CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

TARGET = LoginSystem
SRC = ./src/main.c
SRC1 = ./src/lib.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(SRC1)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
