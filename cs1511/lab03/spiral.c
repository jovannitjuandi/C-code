// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int main (void) {

   int size = 0;
   int row = 1;
   int col = 1;
   int first = 0;
   int last = 0;
   
   printf ("Enter size: ");
   scanf ("%d" , &size);

   int mid = (size/2) + 1;

   // top half
   while (row <= mid) {
      col = 1;
      first = row - 2;
      last = size - row + 1;
   
      if (row == 1 || row == 2) {
         first = 1;
      }
      
      while (col < first) {
            printf ("*-");
            col = col + 2;
      }

      //printing for odd
      if (row%2 == 1) {
      
         while (col >= first && col <= last) {
            printf ("*");
            col = col + 1;
         }

         while (col > last && col <= size) {
            printf ("-*");
            col = col + 2;
         }
      } 

      // printing for even
      else if (row%2 == 0) {

         while (col >= first && col < last) {
            printf ("-");
            col = col + 1;
         }

         while (col >= last && col <= size) {
            printf ("-*");
            col = col + 2;
         }  
      }
      row = row + 1;
      printf ("\n");
   }

   // lower half
   while (row > mid && row <= size) {
      col = 1;
      first = size - row + 1;

      while (col < first) {
            printf ("*-");
            col = col + 2;
      }

      // printing for even
      if (row%2 == 0) {
         last = row;
         
         while (col >= first && col < last) {
            printf ("-");
            col = col + 1;
         }

      }

      // printing for odd
      else if (row%2 == 1) {
         last = row + 1;

         while (col >= first && col < last) {
            printf ("*");
            col = col + 1;
         }

      }
      while (col >= last && col <= size) {
            printf ("-*");
            col = col + 2;
         }
      row = row + 1;
      printf ("\n");
   }

}
