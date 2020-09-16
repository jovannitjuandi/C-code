CC = gcc -Wall -Werror
CFLAGS = -Wall -Werror -std=c11 -g

all: main

fib.o: fib.c fib.h
Graph.o: Graph.c Graph.h
dfs.o: dfs.c dfs.h Graph.o
main.o: main.c fib.h
main: fib.o main.o dfs.o Graph.o
