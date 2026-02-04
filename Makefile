CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99 -lsodium

TARGET = LoginSystem
MAIN = ./src/main.c
USER = ./src/user.c
HELPERS = ./src/helpers.c
lsodium = -lsodium

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(USER) $(HELPERS) $(lsodium)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)
