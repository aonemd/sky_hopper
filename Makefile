CC      = gcc
CFLAGS  = -Wall -Wextra -g
LINKING = -lm -lglut -lGL -lGLU
SRC     = *.c
TARGET  = sky_hopper

all: build run

build:
	$(CC) $(CFLAGS) $(LINKING) -o $(TARGET) $(SRC)

run:
	./$(TARGET)

clean:
	rm $(TARGET)
