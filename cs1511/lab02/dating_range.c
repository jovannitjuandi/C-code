// Jov

//START CODE

#include <stdio.h>

// check eligible
int checker (int x) {

    int check = (x/2) + 7;

    if (check > x) {
	    return 0;
    }
    return 1;
}

// main

int main (void) {

    int age = 0;
    int low = 0;
    int high = 0;
    int ok = 0;

    //get age
    printf ("enter your age: ");
    scanf ("%d", &age);

    ok = checker(age); // check eligible

    if (ok == 0){
	    printf ("you are too young to be dating. \n");
    } else {

	    // calculate low
	    low = (age/2)+7;

	    // calculate high
	    high = (2*(age - low)) + age;

	    // output statement
	    printf ("Your dating range is %d to %d years old.\n", low, high);
    }
    return 0;
}


