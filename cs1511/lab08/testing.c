#include <stdio.h>
#include <stdlib.h>

int main (void) {

int a = 0;
int *p = malloc (12*sizeof(int));
*p = 0;
*(p+1) = 31;
printf ("%p = %d\n", p, *p);
printf ("%p = %d\n", (p+1), *(p+1));
}

/*int evaluate_date (struct date *date) {
   int day = date -> day;
   int month = date -> month;
   int year = date -> year;
   int daypassed [12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
   int evaluation = day + daypassed[month - 1] + (year*365);
   return evaluation;
}*/

/*int evaluate_date (struct date *date) {
   int day = date -> day;
   int month = date -> month;
   int year = date -> year;

   int *p = malloc (12 * sizeof (int));
   *p = 0; *(p+1) = 31; *(p+2) = 59; *(p+3) = 90;
   *(p+4) = 120; *(p+5) = 151; *(p+6) = 181; *(p+7) = 212;
   *(p+8) = 243; *(p+9) = 273; *(p+10) = 304; *(p+11) = 334; 
   
   int evaluation = day + *(p + month-1) + (year*365);
   return evaluation;
}*/
