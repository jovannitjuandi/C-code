// Jovanni (z5213864)

#include <stdio.h>
#include <stdlib.h>

#define MAX_INDEX 10000

typedef struct node {
   int data;
   struct node *next;
} node;

static node *addToEnd (int value, node *head);
static void linkedListImplementation (void);
static void arrayImplementation (void);

int main (void) {
   //linkedListImplementation ();
   arrayImplementation ();
   
   return 0;
}

static void arrayImplementation (void) {
   int input = 0;
   int total = 0;
   int index = 0;
   int array[MAX_INDEX];
   
   while (scanf ("%d", &input) == 1) {
      if (input % 2 == 0) {
         array[index] = input;
         index = index + 1;
         total = total + 1;
      }
   }
   
   index = 0;
   while (index < total) {
      printf ("%d ", array[index]);
      index = index + 1;
   }
  printf ("\n");
}

static void linkedListImplementation (void) {
   int input = 0;
   node *head = NULL;
   
   while (scanf ("%d", &input) == 1) {
      if (input % 2 == 0) {
         head = addToEnd (input, head);
      }
   }
   
   while (head != NULL) {
      printf ("%d ", head -> data);
      head = head -> next;
   }
   printf ("\n");
}

static node *addToEnd (int value, node *head) {
   node *toAdd = calloc (1, sizeof(node));
   toAdd -> data = value;
   if (head == NULL) {
      toAdd -> next = head;
      head = toAdd;
      return head;
   } else {
      node *start = head;
      while (head != NULL) {
         if (head -> next == NULL) {
            toAdd -> next = head -> next;
            head -> next = toAdd;
            return start;
         }
         head = head -> next;
      }
      return start;
   }
}
