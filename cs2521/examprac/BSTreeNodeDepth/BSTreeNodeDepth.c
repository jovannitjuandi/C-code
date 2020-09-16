
#include <stdlib.h>
#include <stdio.h>

#include "BSTree.h"

int depth (BSTree t, int key, int height);

int BSTreeNodeDepth(BSTree t, int key) {
    return depth(t, key, 0);
}

int depth (BSTree t, int key, int height) {
    if (t == NULL) return -1;
    
	if (t->value < key) {
	    return depth (t->right, key, height+1);
	} else if (t->value > key) {
	    return depth (t->left, key, height+1);
	} else return height;
}

