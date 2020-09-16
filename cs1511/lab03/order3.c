// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int main (void) {

   // DECLARE VARIABLES
   
   int num1 = 0;
   int num2 = 0;
   int num3 = 0;

   int large = 0;
   int mid = 0;
   int small = 0;

   // READ FIRST NUMBER
   printf ("Enter integer: ");
   scanf ("%d" , &num1);

   // READ SECOND NUMBER
   printf ("Enter integer: ");
   scanf ("%d" , &num2);

   // READ THIRD NUMBER
   printf ("Enter integer: ");
   scanf ("%d" , &num3);

   // ORDER NUMBER
   if (num1 >= num2 && num1 >= num3) {
      
      large = num1;

      if (num2 >= num3) {

         mid = num2;
         small = num3;

      } else if (num3 >= num2) {

         mid = num3;
         small = num2;      

      }

   } else if (num2 >= num1 && num2 >= num3) {

      large = num2;

      if (num3 >= num1) {

         mid = num3;
         small = num1;

      } else if (num1 >= num3) {

         mid = num1;
         small = num3;

      }
   
   } else if (num3 >= num2 && num3 >= num1) {

      large = num3;

      if (num2 >= num1) {

         mid = num2;
         small = num1;

      } else if (num1 >= num2) {

         mid = num1;
         small = num2;

      }

   }

   // PRINT OUTPUT
   printf ("The integers in order are: %d %d %d \n", small, mid, large);
   
   return 0;
}
