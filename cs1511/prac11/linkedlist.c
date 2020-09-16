#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int         data;
};

struct node *create_node (struct node *new_node, int value) {

   struct node *holder = malloc(sizeof(struct node));

   if (holder == NULL) {
      fprintf(stderr,"Error...\n");
   }

   holder -> data = value;
   holder -> next = new_node;

   return holder;
}

struct node *reverse_list (struct node *head) {
   struct node *hold = head;
   struct node *prev = head;
   struct node *curr = head -> next;
   struct node *next = curr;
   while (curr != NULL) {
      next = curr -> next;
      curr -> next = prev;
      prev = curr;
      curr = next;
   }
   hold -> next = NULL;
   return prev;
}

void print_list (struct node *print) {
   printf ("%d" , print -> data);
   print = print -> next;
   while (print != NULL) {
      printf (" -> %d", print -> data);
      print = print -> next;
   }
   printf ("\n");
}

struct node *get_list (struct node *head) {
   int value = 1;
   while (value != 0) {
      printf ("enter value: ");
      scanf ("%d", &value);
      head = create_node (head, value);
   }
   return head;
}

int sum (struct node *head) {
   int sum = 0;
   while (head != NULL) {
      sum = sum + head -> data;
      head = head -> next;
   }
   return sum;
}

int find_value (struct node *head) {
   int found = 0;
   int find = 0;
   printf ("enter a value to find: ");
   scanf ("%d", &find);
   while (head != NULL) {
      if (head -> data == find) {
         found = 1;
      }
      head = head -> next;
   }
   return found;
}

struct node *last (struct node *head) {
   while (head -> next != NULL) {
      head = head -> next;
   }
   return head;
}

int find_positioned (struct node *head) {
   int count = 1;
   int pos = 0;
   printf ("enter a position to find: ");
   scanf ("%d", &pos);
   while (count < pos && head != NULL) {      
      count = count + 1;
      head = head -> next;
      if (head == NULL) {
         count = pos + 1;
         printf ("not found\n");
         return 0;
      }
   }
   return head -> data;
}

struct node *append (struct node *head) {
   int add = 0;
   printf ("enter a number to add: ");
   scanf ("%d", &add);
   struct node *final = last(head);
   struct node *new = create_node (NULL, add);
   final -> next = new;
return head;
}

struct node *front (struct node *head) {
   int add = 0;
   printf ("enter a number to add: ");
   scanf ("%d", &add);
   struct node *new = create_node (head,add);
   return new;
}

struct node *remove_front (struct node *head) {
   struct node *hold = head;
   head = head -> next;
   free (hold);
   return head;
}

struct node *remove_last (struct node *head) {
   struct node *hold = head;
   struct node *rem = head -> next;
   while (rem -> next != NULL) {
      rem = rem -> next;
      hold = hold -> next;
   }
   hold -> next = NULL;
   free (rem);
   return head;
}

int main (void) {
   struct node *first = NULL;
   struct node *head = get_list (first);
   print_list (head);
   head = reverse_list (head);
   print_list (head);
   printf ("sum is %d\n", sum(head));
   printf ("status of found is %d\n", find_value(head));
   printf ("last item is: %d\n", (last(head) -> data));
   printf ("the item in that position is %d\n", find_positioned(head));
   append (head);
   print_list (head);
   head = front(head);
   print_list(head);
   head = remove_front(head);
   print_list(head);
   head = remove_last(head);
   print_list (head);
}
