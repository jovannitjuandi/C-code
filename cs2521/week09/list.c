#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
    int size;
} list;
typedef struct list *List;

struct node *newNode (int n) {
    struct node *new = malloc (sizeof *new);
    
    new->data = n;
    new->next = NULL;
    return new;
}

List new() {
    list *new = malloc (sizeof *new);
    *new = (list){ .head = NULL, .tail = NULL, .size = 0};
    return new;
}

bool empty(List l) {
    return (l->size == 0);
}

List insert(int n, List l) {
    struct node *new = newNode(n);
    new->next = l->head;
    l->head = new; 
    l->size = l->size + 1;
    return l;
}

List append (List l, int n) {
    struct node *newN = newNode(n);
    List newList = new();
    
    if (empty(l)) {
        newList->head = newN;
        newList->tail = newN;
        newList->size = 1;
        return newList;
    }
    
    newList->head = l->head;
    newList->tail->next = newN;
    newList->tail = newN;
    newList->size = l->size + 1;
    return newList;
}

int head(List l) {
    assert(!empty(l));
    return (l->head->data);
}

List tail(List l) {
    assert(!empty(l));
    if (l->size == 1) return NULL;
    
    List t = new();
    t->head = l->head->next;
    t->tail = l->tail;
    t->size = l->size - 1;
    return t;
}

void print(List l) {
    node *curr = l->head;
    while (curr != NULL) {
        printf("%d->", curr->data);
    }   
    printf("NULL\n");
}

List reverse(List L) {
   if (empty(L))
      return(new());
   else
      return(append(reverse(tail(L)),head(L)));
}

int main (int argc, char **argv) {
    List l = new();
    if (l->head == NULL) {
        printf("Null head\n");
    }
    
    /*append(l, 1);
    append(l, 2);
    append(l, 3);
    append(l, 4);
    append(l, 5);
    append(l, 6);*/
    
    node *curr = newNode(5);
    printf("%d\n", curr->data);
    
    
    append(l, 5);
    print(l);
    
    printf("%d\n", l->size);
    return 0;
}
