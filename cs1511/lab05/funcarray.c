#include <stdio.h>
#include <stdlib.h>

int *arr (int diff) {
    int i = 0;
    int c = 0;
    static int array [100] = {0};
    while (i < 100) {
        array[c] = i;
        i = i + diff;
        c = c + 1;
    }
    array [c] = -1;
    return array;
}

int main (void) {
    int *array = arr(5);
    int i = 0;
    while (*(array + i) != -1) {
        printf ("%02d ", *(array + i));
        i = i + 1;
    }
    printf ("\n");
}
