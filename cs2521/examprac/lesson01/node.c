// INCLUDES
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <sysexits.h>

typedef struct node {
	int data;           // value of this list item
	Node next;          // pointer to node containing next element
} node;

int data(Node n) {
    assert(n != NULL);
    return n->data;
}

Node newNode (int n) {
    Node new = malloc(sizeof(node));
    if (new == NULL) err (EX_OSERR, "couldn't allocate IntList");
    
    new->data = n;
    new->next = NULL;
    return new;
}

void setNext(Node curr, Node next) {
    curr->next = next;
}
