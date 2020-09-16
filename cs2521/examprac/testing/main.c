#include <stdlib.h>
#include <stdio.h>

const int N = 20;

void multiply(int a[N][N], int b[N][N], int c[N][N])
{
    int mult = 0;
    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                mult++;
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    printf("N: %d | mult : %d\n", N, mult);
}

int main (void) {
    int a[N][N];
    int b[N][N];
    int c[N][N];
    multiply(a, b, c);
    return 0;
}
