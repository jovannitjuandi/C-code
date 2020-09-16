#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <sysexits.h>

typedef struct node *Node;

Node newNode(int n);
int data(Node n);
void setNext(Node curr, Node next);
Node getNext(Node curr);
