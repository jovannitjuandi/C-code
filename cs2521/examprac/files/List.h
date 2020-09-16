#include "Node.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <sysexits.h>

typedef struct list *List;

List newList (void);
Node head (List l);
Node tail (List l);
int size (List l);
void insertEnd (List l, int n);
void insertFront (List l, int n);
int deleteEnd (List l);
int deleteFront (List l);
int position (List l, int n);
int itemN (List l, int n);
bool found  (List l, int n);
void deleteItem (List l, int n);
void printList (List l);
void quickSort (List l);
