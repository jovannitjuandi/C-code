
#include "list.h"

int listDeleteLargest(List l) {
    // if empty return
    if (l->head == NULL) return -1;

    // if there's one item
    if (l->head->next == NULL) {
        int d = l->head->value;
        free(l->head);
        l->head = NULL;
        return d;
    }

    int max = l->head->value;
    int p = 0;
    int c = 0;
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
	    if (curr->value > max) {
	        max = curr->value;
	        p = c;
	    }
	    c++;
	}
	
	if (p == 0) {
	    Node n = l->head;
	    l->head = l->head->next;
	    free(n);
	    return max;
	}
	
	Node prev = l->head;
	for (int i = 0; i < (p-1); i++) {
        prev = prev->next;
	}
	Node curr = prev->next;
	
	prev->next = curr->next;
	free(curr);
	
	return max;
}

