
#include <stdlib.h>

#include "BSTree.h"

BSTree Kth(BSTree t, int k, int *count);

int BSTreeGetKth(BSTree t, int k) {
	int count = 0;
	return (Kth(t, k, &count)->value);
}

// Left-Node-Right (LNR) searching
BSTree Kth(BSTree t, int k, int *count) {
    // base case
    if (t == NULL) return NULL;
    
    // search in the left tree 
    BSTree left = Kth(t->left, k, count);
    
    // if k'th smallest is found in left subtree, return it
    if (left != NULL) return left;
    
    // if current element is k'th smallest, return it 
    if ((*count) == k) return t; 
    *count = (*count)+1; 
        
    // if it's not found then search the right tree
    return Kth(t->right, k, count); 
}
