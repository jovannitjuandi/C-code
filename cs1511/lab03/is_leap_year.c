// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int main (void) {

   // DECLARE
   int year;

   // GET INPUT
   printf ("Enter Year: ");
   scanf ("%d", &year);

   // CHECK LEAP
   if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0 )) {
      
      printf ("%d is a leap year.\n" , year);
   
   } else {
      
      printf ("%d is not a leap year.\n" , year);
   
   }

   return 0;
}
