#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    JANUARY,
    FEBRUARY,
    MARCH, 
    APRIL, 
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} month;

typedef struct date {
    int date;
    month month;
    int year;
} date;

int main (int argc, char *argv[]) {
    FILE *out;
    out = fopen (argv[1], "a");

    date array [5];
    int i = 0;
    int d = 7;
    while (i < 5) {
        array[i].date = d;
        array[i].month = JANUARY;
        array[i].year = 2018; 
        fprintf (out, "%02d/%02d/%02d", array[i].date, array[i].month + 1, array[i].year);
        fputs (" THIS IS THE DATE\n", out);
        i = i + 1;
        d = d + 2;
    }
    fclose (out);
    out = fopen (argv[1], "r");
    //FILE *output;
    //output = fopen (argv[1], "r");
    int date = 0;
    int year = 0;
    int month = 0;
    char line[100];
    while (out != '\0') {
        fscanf (out, "%02d/%02d/%02d", &date, &month, &year);
        fgets (line, 100, out);
        printf ("first line is %02d/%02d/%02d\n", date, month, year);
    }

    
}
