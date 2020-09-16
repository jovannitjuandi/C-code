#include <string.h>
#include <stdio.h>

int naiveStringMatch(char *t, char *p)
{
   int i, j;           // indices into t and p
   int counter = 0;
   long n = strlen(t);  // length of string
   long m = strlen(p);  // length of pattern
   for (i = 0; i <= n-m; i++) {
      for (j = 0; j < m; j++) {
         if (t[i+j] != p[j]) {
            counter++;
            printf("i: %d, j: %d, counter: %d\n", i, j, counter);
            break;
         }
      }
      if (j == m) return i; // index of match
   }
   return -1;  // no match
}

int main (void) {
    int where = naiveStringMatch("my string","tri");
    printf("result: %d\n", where);
}
