
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = main.c
EXERCISE_FILE = search.c
COMMON = Graph.c Queue.c Stack.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: main

main: $(SRC_FILES)
	$(CC) $(CFLAGS) -o main $(SRC_FILES)

clean:
	rm -f main

