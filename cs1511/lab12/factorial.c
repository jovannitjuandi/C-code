// Jovanni (z5213864)


long long factorial (long long n) {
   if (n >= 1) {
      return n*factorial (n-1);
   } else {
      return 1;
   }
}
