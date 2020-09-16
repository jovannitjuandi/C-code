// Find and return the minimum positive value
// from the values in a given array.
// By Jovanni (z5213864)
// Written on 2018-08-13
// Angus - Connor (Wed-Kora)


// You need to implement this function

// Returns the minimum positive value from a given array.
// A value is a positive value if it is greater than zero.
// If there are no positive values in a given list,
// the function should return zero.

int arrayPositiveMin(int a[], int size) {
 
   // Implement this function
   int i = 0;
   int minimum = 0;

   while (i < size) {
      if (a[i] > 0) {
         minimum = a[i];
         i = size;
      }
      i = i + 1;
   }
   i = 0;
   while (i < size) {
      if (a[i] <= minimum) {
         if (a[i] > 0) {
            minimum = a[i];
         }
      }
      i = i + 1;
   }
    // You also need to change the return value.
    
    return minimum;

}
