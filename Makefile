CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL2main -lSDL2

TARGET = game.exe
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean 