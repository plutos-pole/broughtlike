TARGET=rgl
CFLAGS=-I ./lib -Wall -Wextra -Wpedantic 
CC=gcc
CFILES:=$(wildcard ./src/*.c)

default:
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES) -lm -lncurses

clean:
	rm $(TARGET)

all:default

debug:
	$(CC) -g -o $(TARGET) $(CFILES) -lm

run:
	./$(TARGET)


