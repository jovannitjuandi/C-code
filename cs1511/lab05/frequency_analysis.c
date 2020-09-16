#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>

int main (void) {
   int letters [26] = {0};
   int c = 0;
   int totalletter = 0;
   int index = 0;

   while (c != EOF) {
      c = getchar();
      c = tolower (c);
      if (c <= 122 && c >= 97) {
         index = c - 97;
         letters[index] = letters[index] + 1;
         totalletter = totalletter + 1;
      } 
   }
   
   int count = 0;
   double freq = 0.0;
   double total = totalletter;
   while (count < 26) {
      char c = (count + 97);
      double freq = (letters[count])/(total);
      printf ("'%c' %lf %d \n", c, freq, letters[count]);
      count = count + 1;
   }
}
