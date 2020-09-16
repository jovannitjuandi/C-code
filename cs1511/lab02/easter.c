// Begin code


#include <stdio.h>

int main (void) {

    int year;

    // get the year
    printf ("Enter Year: ");
    scanf ("%d", &year);
    
    // the WTH part
    int a=year%19;
    int b=year/100;
    int c=year%100;
    int d=b/4;
    int e=b%4;
    int f=(b+8)/25;
    int g=(b-f+1)/3;
    int h=(19*a+b-d-g+15)%30;
    int i=c/4;
    int k=c%4;
    int l=(32+2*e+2*i-h-k)%7;
    int m=(a+11*h+22*l)/451;
    int month =(h+l-7*m+114)/31;
    int p=(h+l-7*m+114)%31;
    int date=p+1;

    // print output
    printf ("Easter is ");
    
    if (month == 3) {
        printf ("March");
    }
    else if (month == 4) {
        printf ("April");
    }
    
    printf (" %d in %d.\n", date, year);
    return 0;
}

