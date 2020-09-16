CC	= gcc -Wall -Werror

all: linkedList main

main: main.c node.h linkedList.h
linkedList.o: linkedList.c linkedList.h

clean:
	-rm -f linkedList linkedList.o
	-rm -f node node.o
