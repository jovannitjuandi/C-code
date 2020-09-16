
#include "list.h"

bool found (List l, int n);
void insert (List l, int n);

List listSetIntersection(List s1, List s2) {
	// TODO
	List ans = newList();
	
	for (Node c1 = s1->head; c1 != NULL; c1 = c1->next) {
        if (found(s2, c1->value) == true && found(ans, c1->value) == false) {
            insert (ans, c1->value);
        }
	}
	return ans;
}

bool found (List l, int n) {
    Node curr = l->head;
    while (curr != NULL) {
        if (curr->value == n) return true;
        curr = curr->next;
    }
    return false;
}

void insert (List l, int n) {
    Node new = newNode(n);
    new->next = l->head;
    l->head = new;
}
