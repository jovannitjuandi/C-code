#include <stdio.h>
int main (void) {
   int a = (5%9);
   printf ("%d\n",a);
}

int gcdRec (int a, int b) {
   if ((a % b == 0) || (b % a == 0)) {
      return b;
   } else {
      b = b % a;
      return gcdRec (b , a);
   }
}

int gcdRec (int a, int b) {
   if (a == 0) {
      return b;
   } else if (b == 0) {
      return a;
   } else if ((a % b == 0) || (b % a == 0)) {
      return b;
   } else if (b > a) {
      b = (b % a);
      return gcdRec (a, b);
   } else {
      a = (a % b);
      return gcdRec (b, a);
   }
}
