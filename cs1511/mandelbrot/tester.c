#include <stdio.h>
int main (void)
   while (abs_w < 2.0 || steps == MAX_STEPS) {
           w.re = (w.re*w.re - w.im*w.im) + c.re;
           w.im = 2*w.re*w.im + c.im;
           steps = steps + 1;
           abs_w = (sqrt(w.re * w.re + w.im * w.im));
       }
       
       if (steps <= MAX_STEPS) {
           steps = NO_ESCAPE;
   }
}
