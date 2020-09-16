
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
    // using while loop
	/*if (t == NULL) return NULL;
	
	BSTree curr = t;
	while (curr->left != NULL) {
	    curr = curr->left;
	}
	return curr;*/
	
	// solving recursively
	if (t == NULL) return NULL;
	
	if (t->left == NULL) return t;
	else return BSTreeGetSmallest(t->left);
	
}

