#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main (void) {
    char p[6] = "THERE";
    int i = 0;
    while (i < 6) {
        printf ("%d\n", isalpha(p[i]));
        i = i + 1;
    }
}
