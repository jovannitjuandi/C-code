#include <stdio.h>

long power(int x, int n) 
{
   long raised = x;   
   for (int i = 0; i <= n; i++) raised *= i;
   return raised;
}

long factorial(int n)
{
   long product = 1;
   int x = 0;
   for (int i = 1; i <= n; i++){
      product *= i;
      x = i;
   }
   
   x++;   
   printf("i checked %d times\n", x);
   return product;
}

int myFunction(int n)
{
   int i = 0;
   while (n > 0) {
      i++;
      n = n/2;
   }
   return i;
}

int main (void) {
    long x;
    x = power(2, 5);
    printf("power is %ld\n", x);   
    
    x = factorial(5);
    printf("factorial is %ld\n", x); 
    
    int y = myFunction(100);
    printf("myFunction is %d\n", y);
}
