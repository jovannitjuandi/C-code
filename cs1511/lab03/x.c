// JOVANNI TJUANDI (z5213864)


#include <stdio.h>

int main (void) {

   int star = 0;
   int row = 1;
   int next = 1;
   int size = 0;

   printf ("Enter size: "); 
   scanf ("%d" , &size);

   while (row <= size) {
   
      while (next <= size) {

         if (next == row || next == (size - row + 1) || next == -(size - row) + 1) {

            printf ("*");

         } else {

            printf ("-");

         }    

         next = next + 1;

      }     
      
      next = 1;
      row = row + 1; 
      printf ("\n");

   }  
   return 0;
}
