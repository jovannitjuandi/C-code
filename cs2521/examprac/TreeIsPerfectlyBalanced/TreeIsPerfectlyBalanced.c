
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int isBalanced(Tree t, bool* balanced) {
	if (t == NULL) {
		return 0;
	}

    // count number of nodes
	int left = isBalanced(t->left, balanced);
	int right = isBalanced(t->right, balanced);
	if (abs(left - right) > 1) {
		*balanced = false;
	}

    // returns number of nodes
	return left + right + 1;
}

bool TreeIsPerfectlyBalanced(Tree t) {
	bool balanced = true;
	isBalanced(t, &balanced);

	return balanced;
}

