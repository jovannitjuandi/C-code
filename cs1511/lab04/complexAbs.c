// Calculate the magnitude of a complex number
// By Jovanni (z5213864)
// Written on 2018-08-13
// Angus - Connor (wed-kora)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// DO NOT CHANGE THIS STRUCT
typedef struct _complex {
    double real;
    double imaginary;
} complex;

double complexAbsolute(complex c);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {

    complex c;

    printf("Enter the real part: ");
    scanf("%lf", &c.real);

    printf("Enter the imaginary part: ");
    scanf("%lf", &c.imaginary);

    // Calculate the absolute value.
    double absoluteValue = complexAbsolute(c);

    printf("The absolute value is %.2lf.\n", absoluteValue);

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

// Calculate the magnitude (absolute value) of a complex number.
double complexAbsolute(complex c) {
    // PUT YOUR CODE HERE;
    double modsq = (c.real*c.real) + (c.imaginary*c.imaginary);
    double modulus = sqrt(modsq);
    return modulus; // CHANGE THIS TO YOUR RETURN VALUE
}
