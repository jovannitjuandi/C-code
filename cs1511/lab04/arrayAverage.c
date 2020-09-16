// Find the average of the values in a given array.
// By Jovanni (z5213864)
// Written on 2018-08-13
// Angus - Connor (Wed-Kora)

// You need to implement this function

// Calculates the average of all the values in a given array,
// and returns the average value.
#include <stdio.h>
#include <assert.h>

#define MAX_LENGTH 1024

double arrayAverage(int a[], int size) {
   int i = 0;
   double sum = 0.0;
   double average = 0.0;
   while (i < size) {
      sum = sum + a[i];
      i = i + 1;
   }
   average = sum / size;
   
   return average;
}
