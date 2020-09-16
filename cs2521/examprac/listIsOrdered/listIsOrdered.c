
#include "list.h"

bool listIsOrdered(List l) {
    // if list is empty or single item
    if (l->head == NULL || l->head->next == NULL) return true;

    // more than one item
	Node curr = l->head;
	int n;
	
	// check if its ascending or descending
	if (curr->value < curr->next->value) {
	    // ascending
	    while (curr != NULL){
	        if (curr->next == NULL) break;
	        
	        n = curr->value;
	        if (curr->next->value < n) return false;
	        curr = curr->next;
	    }
	} else {
	    // descending
	    while (curr != NULL){
	        if (curr->next == NULL) break;
	        
	        n = curr->value;
	        if (curr->next->value > n) return false;
	        curr = curr->next;
	    }
	}
	
	return true;
}

