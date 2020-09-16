
#include <stdlib.h>

#include "tree.h"

int max (int a, int b) {
    return a > b ? a : b;
}

int TreeHeight(Tree t) {
    if (t == NULL) return -1;
    
    else return max(TreeHeight(t->left), TreeHeight(t->right)) + 1;
}

