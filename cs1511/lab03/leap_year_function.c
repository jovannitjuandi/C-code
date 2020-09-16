// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

int isLeapYear(int year);

int main (void) {
   
   int year;
   printf ("Enter Year: ");
   scanf ("%d" , &year);
   int leap = isLeapYear(year);
   
   if (leap == 0) {

      printf ("%d is not a leap year.\n" , year);

   } else {

      printf ("%d is a leap year.\n" , year);

   }

   return 0;
}

int isLeapYear(int year) {

   if (year % 100 == 0) {

      if (year % 400 == 0) {
      
         return 1;
      
      } else {
         
         return 0; 

      }
   
   } else if (year % 4 == 0) {
      
      return 1;

   } else {
      
      return 0; 
      
   }

}
