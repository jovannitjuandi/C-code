// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int outlier (num) {

   if (num > 25 || num < 5) {
      
      return 1;      
      
   } else {

      return 0;

   }
   return 0;

}

int main (void) {

   int read = 1;
   int num = 0;
   int out = outlier (num);
   int total_out = 0;

   while (read == 1) {

      printf ("Enter number: ");
      read = scanf ("%d" , &num);
      out = outlier (num);
      
      if (out == 1) {
         
         total_out = total_out + 1;

      }
   
   }
   
   if (total_out != 0) {
      total_out = total_out - 1;
   }

   printf ("\nOutliers: %d\n" , total_out);
   return 0;
}
