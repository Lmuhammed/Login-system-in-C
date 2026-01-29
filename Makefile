CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99

TARGET = LoginSystem
MAIN = ./src/main.c
USER = ./src/user.c
HELPERS = ./src/helpers.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(USER) $(HELPERS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
