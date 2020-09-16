#include <stdio.h>
#include <stdlib.h>

int encrypt(int c, int shift) {
   int new = 0;
   if (c <= 90 && c >= 65) {
      new = c + shift; 
         while (new > 90) {
            new = new - 26;
         }
         while (new < 65) {
            new = new + 26;
         }
   } else if (c >= 97 && c<= 122) {
      new = c + shift;
         while (new > 122) {
            new = new - 26;
         }
         while (new < 97) {
            new = new + 26;
         }
   } else {
      new = c;
   }
   return new;
}

int main (int argc, char* argv[]) {
   int c = 0;
   int shift = atoi(argv[1]);
   int new = 0;
   int index = 0;
   while (c != EOF) {
      c = getchar();
      if (c != EOF) {
         new = encrypt (c,shift);
         putchar(new);
      }
      index = index + 1;
   }
   return 0;
}
