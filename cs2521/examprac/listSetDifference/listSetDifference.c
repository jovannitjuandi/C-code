
#include "list.h"

bool found (List l, int n);
void insert (List l, int n);

List listSetDifference(List l1, List l2) {
	// TODO
	List ans = newList();
	
	for (Node curr = l1->head; curr != NULL; curr = curr->next) {
	    if (found(l2, curr->value) == false) {
	        insert(ans, curr->value);
	    }
	}
	return ans;
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
