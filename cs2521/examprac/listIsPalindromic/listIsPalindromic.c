
#include "list.h"

bool listIsPalindromic(List l) {
	// TODO
	Node h = l->first;
	Node t = l->last;
	for (int i = 0; i < (l->size)/2; i++) {
	    if (h->value != t->value) return false;
	    h = h->next;
	    t = t->prev;
	}
	return true;
}

