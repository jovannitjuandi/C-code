// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int main (void) {

   int n = 0;
   printf ("Enter number: ");
   scanf ("%d" , &n);
   int count = 1;

   while (count < n) {

      if (count % 3 == 0) {
      
         printf ("%d\n" , count);      
      
      } else if (count % 5 == 0) {

         printf ("%d\n" , count);

      }
      
      count = count + 1;

   }

   return 0;
}
