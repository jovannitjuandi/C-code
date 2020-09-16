// INCLUDES
#include "linkedList.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <err.h>
#include <stdbool.h>
#include <sysexits.h>

// MAIN FUNCTION
int main (int argc, char *argv[]) {
    /*// check node functions
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
    assert(position(l4, 9) == 4);*/
    
    return 0;
}
