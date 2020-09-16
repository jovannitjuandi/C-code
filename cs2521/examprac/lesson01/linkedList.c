// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <sysexits.h>

// STRUCTS
typedef struct node *Node;
typedef struct node {
	int data;           // value of this list item
	Node next;          // pointer to node containing next element
} node;

typedef struct list *List;
typedef struct list {
	int size;           // number of elements in list
	Node head;
	Node tail;
} list;

// FUNCTION PROTOTYPES
List newList (void);
int data(Node n);
Node head (List l);
Node tail (List l);
int size (List l);
void insertEnd (List l, int n);
void insertFront (List l, int n);
int deleteEnd (List l);
int deleteFront (List l);
int position (List l, int n);
bool found  (List l, int n);
void deleteItem (List l, int n);
Node newNode (int n);
void printList (List l);


// MAIN FUNCTION
int main (int argc, char *argv[]) {
    // check node functions
    Node n1 = newNode(5);
    assert(data(n1) == 5);
    
    // check insert and delete functions
    List l1 = newList();
    assert(head(l1) == NULL);
    assert(tail(l1) == NULL);
    assert(size(l1) == 0);
    
    insertEnd(l1, 4);
    assert(data(head(l1)) == 4);
    assert(data(tail(l1)) == 4);
    assert(size(l1) == 1);
    
    
    insertEnd(l1, 3);
    assert(data(head(l1)) == 4);
    assert(data(tail(l1)) == 3);
    assert(size(l1) == 2);
    
    insertEnd(l1, 2);
    assert(data(head(l1)) == 4);
    assert(data(tail(l1)) == 2);
    assert(size(l1) == 3);
    
    insertFront(l1, 5);
    assert(data(head(l1)) == 5);
    assert(data(tail(l1)) == 2);
    assert(size(l1) == 4);
    
    insertFront(l1, 6);
    assert(data(head(l1)) == 6);
    assert(data(tail(l1)) == 2);
    assert(size(l1) == 5);
    
    insertFront(l1, 7);
    assert(data(head(l1)) == 7);
    assert(data(tail(l1)) == 2);
    assert(size(l1) == 6);
    
    deleteEnd(l1);
    assert(data(head(l1)) == 7);
    assert(data(tail(l1)) == 3);
    assert(size(l1) == 5);
    
    printList(l1);
    
    List l2 = newList();
    assert(head(l2) == NULL);
    assert(tail(l2) == NULL);
    assert(size(l2) == 0);
    
    insertEnd(l2, 9);
    assert(data(head(l2)) == 9);
    assert(data(tail(l2)) == 9);
    assert(size(l2) == 1);
    
    deleteEnd(l2);
    assert(head(l2) == NULL);
    assert(tail(l2) == NULL);
    assert(size(l2) == 0);
    
    printList(l2);
    
    List l3 = newList();
    assert(head(l3) == NULL);
    assert(tail(l3) == NULL);
    assert(size(l3) == 0);
    
    insertFront(l3, 8);
    assert(data(head(l3)) == 8);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 1);
    
    insertFront(l3, 6);
    assert(data(head(l3)) == 6);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 2);
    
    insertFront(l3, 4);
    assert(data(head(l3)) == 4);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 3);
    
    insertFront(l3, 2);
    assert(data(head(l3)) == 2);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 4);
    
    deleteFront(l3);
    assert(data(head(l3)) == 4);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 3);
    
    deleteFront(l3);
    assert(data(head(l3)) == 6);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 2);
    
    deleteFront(l3);
    assert(data(head(l3)) == 8);
    assert(data(tail(l3)) == 8);
    assert(size(l3) == 1);
    
    deleteFront(l3);
    assert(head(l3) == NULL);
    assert(tail(l3) == NULL);
    assert(size(l3) == 0);
    
    printList(l3);
    
    // list and node function checks
    List l4 = newList();
    insertEnd(l4, 5);
    insertEnd(l4, 7);
    insertEnd(l4, 9);
    insertFront(l4, 7);
    insertFront(l4, 6);
    insertFront(l4, 8);
    
    printList(l4);
    
    assert(found(l4, 5) == true);
    assert(found(l4, 3) == false);
    assert(found(l4, 8) == true);
    assert(found(l4, 2) == false);
    assert(found(l4, 6) == true);
    assert(found(l4, 1) == false);
    
    deleteItem(l4, 7);
    assert(data(head(l4)) == 8);
    assert(data(tail(l4)) == 9);
    assert(size(l4) == 5);
    
    printList(l4);
    
    deleteItem(l4, 7);
    assert(data(head(l4)) == 8);
    assert(data(tail(l4)) == 9);
    assert(size(l4) == 4);
    
    printList(l4);
    
    assert(position(l4, 8) == 1);
    assert(position(l4, 6) == 2);
    assert(position(l4, 5) == 3);
    assert(position(l4, 9) == 4);
    
    return 0;
}

// FUNCTION IMPLEMENTATION
List newList(void) {
    List l = malloc(sizeof(list));
    if (l == NULL) err (EX_OSERR, "couldn't allocate IntList");
    
    l->size = 0;
    l->head = NULL;
    l->tail = NULL;
    
    return l;
}

int data(Node n) {
    assert(n != NULL);
    return n->data;
}

Node head (List l) {
    return l->head;
}

Node tail (List l) {
    return l->tail;
}

int size (List l) {
    return l->size;
}

void insertEnd (List l, int n) {
    Node new = newNode(n);
    
    if (size(l) == 0) {
        l->tail = new;
        l->head = new;
        l->size = l->size + 1;
        return;
    }
    
    l->tail->next = new;
    l->tail = new;
    l->size = l->size + 1;
    return;
}

void insertFront (List l, int n) {
    Node new = newNode(n);
    
    if (size(l) == 0) {
        l->tail = new;
        l->head = new;
        l->size = l->size + 1;
        return;
    }
    
    new->next = l->head;
    l->head = new;
    l->size = l->size + 1;
    return;
}

int deleteEnd (List l) {
    assert(size(l) != 0);
    int d;
    
    if (size(l) == 1) {
        Node deleted = l->tail;
        d = data(deleted);
        free(deleted);
        
        l->head = NULL;
        l->tail = NULL;
        l->size = l->size - 1;
        
        return d;
    } 
    
    Node prev = l->head;
    Node curr = l->head->next;
    
    while (curr->next != NULL) 
    {
        prev = prev->next;
        curr = curr->next;
    }
    
    prev->next = NULL;
    l->tail = prev;
    l->size = l->size - 1;
    d = data(curr);
    free(curr);
    
    return d;

}

int deleteFront (List l) {
    assert(size(l) != 0);
    int d;
    
    if (size(l) == 1) {
        Node deleted = l->head;
        d = data(deleted);
        free(deleted);
        
        l->head = NULL;
        l->tail = NULL;
        l->size = l->size - 1;
        
        return d;
    }
    
    Node prev = l->head;
    Node curr = l->head->next;
    
    l->head = curr;
    l->size = l->size - 1;
    d = data(prev);
    free(prev);
    
    return d;
}

bool found  (List l, int n) {
    for (Node curr = l->head; curr != NULL; curr = curr->next) {
        if (data(curr) == n) return true;
    }
    return false;
}

void deleteItem (List l, int n) {
    assert(size(l) != 0);
    assert(found(l, n) == true);

    Node prev = l->head;
    Node curr = l->head->next;
    
    if (size(l) == 1) {
        Node deleted = l->head;
        free(deleted);
        
        l->head = NULL;
        l->tail = NULL;
        l->size = l->size - 1;
    }
    
    while (curr != NULL) {
        if (data(curr) == n) {
            l->size = l->size - 1;
            prev->next = curr->next;
            free(curr);
            return;
        }
        prev = prev->next;
        curr = curr->next;
    }
}

int position (List l, int n) {
    int p = 0;
    
    for (Node curr = l->head; data(curr) != n; curr = curr->next) {
        p++;
    }
    
    return (p+1);
}

Node newNode (int n) {
    Node new = malloc(sizeof(node));
    if (new == NULL) err (EX_OSERR, "couldn't allocate IntList");
    
    new->data = n;
    new->next = NULL;
    return new;
}

void printList (List l) {
    Node current = l->head;
    while (current != NULL) {
        printf("%d->", data(current));
        current = current->next;
    }
    printf("NULL\n");
}   
