
#include "list.h"

bool found (List l, int n);
void insert (List l, int n);

List listSetUnion(List s1, List s2) {
	// TODO
	List all = newList();
	
	Node curr = s1->head;
	while (curr != NULL) {
	    insert(all, curr->value);
	    curr = curr->next;
	}
	
	curr = s2->head;
	while (curr != NULL) {
	    if (found(all, curr->value) == false) {
	        insert (all, curr->value);
	    }
	    curr = curr->next;
	}
	
	return all;
}

bool found (List l, int n) {
    Node curr = l->head;
    while (curr != NULL) {
        if (curr->value == n) return true;
        curr = curr->next;
    }
    return false;
}

void insert (List l, int n) {
    Node new = newNode(n);
    new->next = l->head;
    l->head = new;
}
