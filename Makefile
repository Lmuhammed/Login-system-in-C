CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

TARGET = LoginSystem
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
