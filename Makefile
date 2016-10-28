CC=gcc
CFLAGS=-W -Wall
SOURCES=$(wildcard sources/*.c)
BUILD=./builds
EXEC=main.out

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(BUILD)/$(EXEC)
