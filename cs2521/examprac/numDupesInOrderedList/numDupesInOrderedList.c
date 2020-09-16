
#include "list.h"

int numDupesInOrderedList(List l) {
    // best case scenario
    if (l->head == NULL || l->head->next == NULL) return 0;

	int dup = 0;
	Node curr = l->head;
	int prev = curr->value;
	curr = curr->next;
	
	while (curr != NULL) {
	    
	    if (curr->value == prev) dup++;
	    
	    prev = curr->value;
	    curr = curr->next;
	}
	
	return dup;
}


