// Print Wondrous
// Created by
//  Jovanni (z5213864)
//  ... (z0000000)
// Created on 2018-08-14
// Angus - Connor (Wed-KOra)

#include <stdio.h>
#include <stdlib.h>

int printWondrous(int num);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {
    // Get the number.
    int number;
    printf ("Enter a number: ");
    scanf("%d", &number);

    // Call printWondrous and save the count.
    int count = printWondrous(number);

    printf("The count is %d.\n", count);

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

int printWondrous(int num) {
    // PUT YOUR CODE HERE
    int count = 0;
    printf ("%d " , num);
    while (num > 1) {
       if (num % 2 == 0) {
          num = num / 2;
          printf ("%d " , num);
       } else { 
          if (num != 1) {
             num = 3*num + 1;
             printf ("%d " , num);
          } 
       }
       count = count + 1;
    } 
    printf ("\n");
    count = count + 1;

    return count; // CHANGE THIS TO YOUR RETURN VALUE
}
