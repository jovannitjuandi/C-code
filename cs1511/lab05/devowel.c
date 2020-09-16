#include <stdio.h>

int is_vowel(int character);

int main (void) {
   int c = 0;
   int vowel = 0;
   while (c != EOF) {
      c = getchar();
      vowel = is_vowel(c);
      if (vowel == 0) {
         putchar(c);
      }
   }
   return 0;
}

int is_vowel(int c) {
   if (c == 97 || c == 101 || c == 105 || c == 111 || c == 117 || c == EOF) {
      return 1;
   }
   return 0;
}
