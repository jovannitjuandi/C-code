
#include <stdlib.h>

#include "tree.h"

bool isOdd(Tree t) {
    return (((t->value)%2) == 1);
}

int TreeSumOdds(Tree t) {
    if (t == NULL) return 0;
    
    if (isOdd(t) == true) {
        return (t->value) + TreeSumOdds(t->left) + TreeSumOdds(t->right);
    } else {
        return TreeSumOdds(t->left) + TreeSumOdds(t->right);
    }
}

