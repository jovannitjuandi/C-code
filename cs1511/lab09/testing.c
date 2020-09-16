#include <stdio.h>
#define LAST 15
int main (void) {
   int num = 0;
   int count = 0;
   int a [15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   
   printf ("enter number : ");
   scanf ("%d", &num);

   while (a[count + 1] < LAST - 1) {
      if (a[count] == num) {
         a[count] = a[count + 1];
      }
      count = count + 1;
   }
}
