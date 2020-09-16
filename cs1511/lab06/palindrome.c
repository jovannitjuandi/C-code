//made by Jovanni (z5213864)
//tutorial (Angus - Connor)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 4096

int main (int argc, char *argv[]) {
   char line [MAX_LINE];
   int i = 0;
   int half = 0;
   int stat = 1;
   int c = 0;

   printf ("Enter a string: ");
   fgets(line, MAX_LINE, stdin);
   i = strlen (line) - 2;
   half = i/2; 

   if (strlen(line) >= 2) {
      while (c <= half) {
         if (tolower(line[c]) != tolower(line[i - c])) {
            stat = 0;
            c = half;
         }
         c = c + 1;
      }
   }
   
   if (stat == 0) {
      printf ("String is not a palindrome\n");
   } else {
      printf ("String is a palindrome\n");
   }
return 0;
}
