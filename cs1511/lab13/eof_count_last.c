// Jovanni (z5213864)

#include <stdio.h>
#include <stdlib.h>

#define MAX_INDEX 10000

typedef struct node {
   int data;
   struct node *next;
} node;

static node *addList (int value, node *head);
static void arrayImplementation (void);
static void linkedListImplementation (void);

int main (void) {
   //arrayImplementation ();
   linkedListImplementation ();
}

static node *addList (int value, node *head) {
   node *toAdd = malloc (sizeof(node));
   toAdd -> data = value;
   toAdd -> next = head;
   head = toAdd;
   return head;
}

static void linkedListImplementation (void) {
   int input = 0;
   int total = 0;
   node *head = NULL;
   
   while (scanf("%d", &input) == 1) {
      head = addList (input, head);
   }
   
   while (head != NULL) {
      if (head -> data == input) {
         total = total + 1;
      }
      head = head -> next;
   }
   
   printf ("%d\n", total);
}

static void arrayImplementation (void) {
   int input = 0;
   int count = 0;
   int index = 0;
   int total = 0;
   int array[MAX_INDEX];
   
   while (scanf("%d", &input) == 1) {
      array[count] = input;
      count = count + 1;
   }
   
   while (index < count) {
      if (array[index] == input) {
         total = total + 1;
      }
      index = index + 1;
   }
   printf ("%d\n", total);
}
