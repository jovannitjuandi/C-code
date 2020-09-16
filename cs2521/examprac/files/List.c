// INCLUDES
#include "List.h"

// STRUCTS
typedef struct list {
	int size;           // number of elements in list
	Node head;
	Node tail;
} list;

// FUNCTION IMPLEMENTATION
List newList(void) {
    List l = malloc(sizeof(list));
    if (l == NULL) err (EX_OSERR, "couldn't allocate List");
    
    (*l) = (list){.size = 0, .head = NULL, .tail = NULL};
    return l;
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
        (*l) = (list){.size = size(l)+1, .head = new, .tail = new};
    } else {
        setNext(l->tail, new);
        l->tail = new;
        l->size = size(l) + 1;
    }
}

void insertFront (List l, int n) {
    Node new = newNode(n);
    
    if (size(l) == 0) {
        (*l) = (list){.size = size(l)+1, .head = new, .tail = new};
    } else {
        setNext(new, l->head);
        l->head = new;
        l->size = size(l) + 1;
    }
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
    Node curr = getNext(l->head);
    
    while (getNext(curr) != NULL) 
    {
        prev = getNext(prev);
        curr = getNext(curr);
    }
    
    setNext(prev, NULL);
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
    Node curr = getNext(l->head);
    
    l->head = curr;
    l->size = l->size - 1;
    d = data(prev);
    free(prev);
    
    return d;
}

bool found  (List l, int n) {
    for (Node curr = l->head; curr != NULL; curr = getNext(curr)) {
        if (data(curr) == n) return true;
    }
    return false;
}

void deleteItem (List l, int n) {
    assert(size(l) != 0);
    assert(found(l, n) == true);

    Node prev = l->head;
    Node curr = getNext(l->head);
    
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
            setNext(prev, getNext(curr));
            free(curr);
            return;
        }
        prev = getNext(prev);
        curr = getNext(curr);
    }
}

int position (List l, int n) {
    assert(found(l, n) == true);
    int p = 0;
    
    for (Node curr = l->head; data(curr) != n; curr = getNext(curr)) p++;
    
    return (p+1);
}

int itemN (List l, int n) {
    assert(n <= size(l));
    Node curr = head(l);
    for (int i = 1; i < n; i++) {
        curr = getNext(curr);
    }   
    return data(curr);
}

void printList (List l) {
    Node current = l->head;
    while (current != NULL) {
        printf("%d->", data(current));
        current = getNext(current);
    }
    printf("NULL\n");
}   


////////////////////////////////////////////////////////////////
// QUICKSORT ALGORITHM
void quickSort (List l) {

}
