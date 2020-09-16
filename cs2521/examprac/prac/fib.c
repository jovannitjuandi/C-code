#include "fib.h"

int fib(int n)
{
   printf("fib called\n");
   assert(n > 0);
   if (n == 1 || n == 2)
      return 1;
   else
      return fib(n-1) + fib(n-2);
}


