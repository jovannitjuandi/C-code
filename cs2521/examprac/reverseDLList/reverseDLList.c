
#include "list.h"

void reverseDLList(List l) {
	if (l->first == NULL || l->first->next == NULL) return;
	
	l->last = l->first;
	Node curr = l->first;
	Node prev = NULL;
	Node next = NULL;
	
	while (curr != NULL) {
	    next = curr->next;
	    curr->next = prev;
	    curr->prev = next;
	    
	    prev = curr;
	    curr = next;
	}
	
	l->first = prev;
}

