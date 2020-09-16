// Prints out an array.
// Created by
//  BY Jovanni (z5213864)
// Created on 2018-08-13
// Angus - Connor (Wed-Kora)

#include <stdio.h>
#include <assert.h>

void show_array(int size, int array[size]);

// DO NOT CHANGE THIS MAIN FUNCITON
int main(int argc, char *argv[]) {
    // Get the array size.
    int size;
    printf("Enter array size: ");
    assert(scanf("%d", &size) == 1);
    assert(size > 0);

    // Declare the array.
    int array[size];

    printf("Enter array values: ");
    // Initialise the array values.
    int i = 0;
    while (i < size) {
        assert(scanf("%d", &array[i]) == 1);
        i = i + 1;
    }

    show_array(size, array);

    return 0;
}

// Print the array in the format [1, 2, 3, ...]
void show_array(int size, int array[size]) {
    // Put your code here
    int index = 0;
    printf ("[");
    while (index < size - 1) {
       printf ("%d, ",array[index]);
       index = index + 1;
    }
    printf ("%d]\n", array [index]);
}
