// JOV

#include <stdio.h>

int main (void) {

    // declare var
    int money = 10;
    int cost = 0;
    int scoop = 0;

    printf ("How many scoops? ");
    scanf ("%d",&scoop);

    printf ("How many dollars does each scoop cost? ");
    scanf ("%d",&cost);

    int total = scoop*cost;

	    if (total > 10) {
		    printf ("oh no, you don't have enough money :( \n");
	    } else {
		    printf ("You have enough money!\n");
	    }
    return 0;
}
