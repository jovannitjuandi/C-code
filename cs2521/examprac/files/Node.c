#include "Node.h"

typedef struct node {
	int data;           // value of this list item
	Node next;          // pointer to node containing next element
} node;

Node newNode(int n) {
    Node new = malloc(sizeof(node));
    if (new == NULL) err (EX_OSERR, "couldn't allocate Node");
    
    new->data = n;
    new->next = NULL;
    return new;
}

int data(Node n) {
    assert(n != NULL);
    return n->data;
}

void setNext(Node curr, Node next) {
    curr->next = next;
}

Node getNext(Node curr) {
    return curr->next;
}
