
#include "tree.h"

Tree TreeCopy(Tree t, int depth) {
	if (depth < 0 || t == NULL) return NULL; 
	
	Tree new = malloc(sizeof(*new));
	*new = (struct node){.value = t->value, .left = TreeCopy(t->left, depth-1), .right = TreeCopy(t->right, depth-1)};
	
	return new;
}
