//JOV

#include <stdio.h>

int main (void) {

    int num1 = 0;
    int num2 = 0;

    printf("Please enter two integers: ");
    scanf("%d %d", &num1, &num2);

    int sum = num1 + num2;

    printf ("%d + %d = %d \n" , num1, num2, sum);
    return 0;
}
