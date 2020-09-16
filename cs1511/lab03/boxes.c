// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int main (void) {

   int box = 0;
   int size = 0;

   printf ("How many boxes: ");
   scanf ("%d" , &box);
   size = (box*2) + ((box - 1)*2) + 1;

   
   
   int row = 1;
   int col = 1;
   int mid = (size/2) + 1;
   int first = 0;
   int last = 0;

   if (box > 0) {
      // printing for top rows
      while (row < mid) {

         // printing for odd
         if (row%2 == 1) {

            first = row;
            last = (size - row + 1);

            while (col < first) {
               printf ("# ");
               col = col + 2;
            }

            while (col >= first && col <= last) {
               printf ("#");
               col = col + 1;
            }

            while (col > last && col <= size) {
               printf (" #");
               col = col + 2;
            }

         }
         
         // printing for even
         if (row%2 == 0) {

            first = row - 1;
            last = size - row + 1;
            
            while (col <= first) {
               printf ("# ");
               col = col + 2;
            }   
            
            while (col > first && col < last) {
               printf (" ");
               col = col + 1;
            }   

            while (col >= last && col <= size) {
               printf (" #");
               col = col + 2;
            }

         }

         row = row + 1;
         col = 1;
         printf ("\n");

      }

      // print in middle line
      col = 1;
      while (row == mid) {
         while (col < (size-1)) { 
            printf ("# ");
            col = col + 2;
         }
         row = row + 1;
      }
      printf ("#\n");
      
      // print lower rows
      while (row > mid && row <= size) {

         col = 1;
         // printing odd lines
         if (row%2 == 1) {

            first = size - row - 1;
            last = row + 1;

            while (col <= first) {
               printf ("# ");
               col = col + 2;
            }

            while (col > first && col < last) {
               printf ("#");
               col = col + 1;
            }

            while (col >= last && col <= size) {
               printf (" #");
               col = col + 2;
            }

         }

         // printing for even       
         if (row%2 == 0) {

            first = size - row;
            last = row;

            while (col <= first) {
               printf ("# ");
               col = col + 2;
            }
            
            while (col > first && col < last) {
               printf (" ");
               col = col + 1;
            }

            while (col >= last && col <= size) {
               printf (" #");
               col = col + 2;
            }
         }
      printf ("\n");
      row = row + 1;
      }
   }
}
