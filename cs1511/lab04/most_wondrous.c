#include <stdio.h>

int main (void) {
   unsigned long long int num = 0;
   int count = 0;
   printf("Enter number: ");
   scanf ("%d" , &num);
   printf ("%d " , num);
   while (num > 1) {
   if (num % 2 == 0) {
      num = num / 2;
      printf ("%d " , num);
   } else { 
      if (num != 1) {
       num = 3*num + 1;
       printf ("%d " , num);
      } 
   }
      count = count + 1;
   } 
   printf ("\n");
   count = count + 1;
   printf ("The count is %d\n", count);

   return 0;
}
