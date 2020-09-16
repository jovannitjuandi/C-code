// JOVANNI TJUANDI (z5213864)

#include <stdio.h>
int number (num) {

   num = num - 1;
   if (num < 0) {
      num = num + 10;
   }
   return num;

}

int main (void) {

   int size = 0;

   printf ("Enter size: ");
   scanf ("%d" , &size);

   // CALCULATION

   int length = size * ((size/2) + 1) + (size/2);
   int start = (length % 10) - 1;
   if (start < 0) {
      start = 9;
   }
   int num = start;
   int row = 1;
   int col = 1;
   int first = 0;
   int last = 0;
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
            printf ("%d-", num);
            col = col + 2;
            num = number(num);
      }

      //printing for odd
      if (row%2 == 1) {
      
         while (col >= first && col <= last) {
            printf ("%d", num);
            col = col + 1;
            num = number(num);
         }

         while (col > last && col <= size) {
            printf ("-%d", num);
            col = col + 2;
            num = number(num);
         }
      } 

      // printing for even
      else if (row%2 == 0) {

         while (col >= first && col < last) {
            printf ("-");
            col = col + 1;
         }

         while (col >= last && col <= size) {
            printf ("-%d", num);
            col = col + 2;
            num = number(num);
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
            printf ("%d-", num);
            col = col + 2;
            num = number(num);
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
            printf ("%d", num);
            col = col + 1;
            num = number(num);
         }
      }
      while (col >= last && col <= size) {
            printf ("-%d", num);
            col = col + 2;
            num = number(num);
      }
      row = row + 1;
      printf ("\n");
   }
}
