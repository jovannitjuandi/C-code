// jovanni (z5213864)

#include <stdlib.h>
#include "Set.h"

typedef int item;

struct node {
   item value;
   struct node *next;
};

typedef struct _set {
   int size;
   struct node *member;
} set;

Set newSet (void) {
   Set new_set = calloc (1, sizeof(set));
   new_set -> member = NULL;
   new_set -> size = 0;

   return new_set;
}

void destroySet (Set s) {
   free (s);
}

void setAdd(Set s, item item) {
   if (setContains (s, item) == 0) {
      struct node *new = calloc (1, sizeof(struct node));
      new -> value = item;
      new -> next = s -> member;
      s-> member = new;
   }
}

void setRemove(Set s, item item) {
   if (s == NULL) {
      
   } else if (s -> member -> value == item) {
      struct node *temp = s -> member;
      s -> member = temp -> next;
      free (temp);
   } else {
      struct node *prev = s -> member;
      struct node *curr = prev -> next;
      while (curr != NULL) {
         curr = prev -> next;
         if (curr -> value == item) {
            prev -> next = curr -> next;
            free (curr);
            break;
         }
         prev = prev -> next;
         curr = curr -> next;
      }
   }
}

bool setContains(Set s, item item) {
   if (s -> member == NULL) {
      return 0;
   } else if (s -> member -> value == item) {
      return 1;
   } else {
      struct node *curr = s -> member;
      while (curr != NULL) {
         if (curr -> value == item) {
            return 1;
         }
         curr = curr -> next;
      }
      return 0;
   }
}

int setSize(Set s) {
   int count = 0;
   struct node *head = s -> member;
   while (head != NULL) {
      count = count + 1;
      head = head -> next;
   }
   return count;
}

Set setUnion(Set a, Set b) {
   Set unite = newSet();
   struct node *setA = a -> member;
   struct node *setB = b -> member;
   
   while (setA != NULL) {
      setAdd (unite, setA -> value);
      setA = setA -> next;
   }
   
   while (setB != NULL) {
      setAdd (unite, setB -> value);
      setB = setB -> next;
   }
   return unite;
}

Set setIntersection(Set a, Set b) {
   Set intersect = newSet();
   struct node *setA = a -> member;
   struct node *setB = b -> member;
   
   while (setA != NULL) {
      setB = b -> member;
      while (setB != NULL) {
         if (setA -> value == setB -> value) {
            setAdd (intersect, setB -> value);
         }
         setB = setB -> next;
      }
      setA = setA -> next;
   }
   return intersect;
}

bool setSubset(Set a, Set b) {
   Set inter = setIntersection (a, b);
   if (setSize (inter) == 0 || setSize (a) > setSize (b)) {
      return 0;
   } else {
      if (setEqual (inter, a) == 1) {
         return 1;
      } else {
         return 0;
      }
   }
}

bool setEqual(Set a, Set b) {
   struct node *setA = a -> member;
   struct node *setB = b -> member;
   
   if (setSize(a) != setSize(b)) {
      return 0;
   }
   int found = 0;
   while (setA != NULL) {
   found = 0;
   setB = b -> member;
      while (setB != NULL) {
         if (setB -> value == setA -> value) {
            found = 1;
         }
         setB = setB -> next;  
      }
      if (found == 0) {
         return 0;
      }
      setA = setA -> next;
   }
   
   return 1;
}

