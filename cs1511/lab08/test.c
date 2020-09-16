int main (void) {
int date = 0;
int month = 0;
int year = 0;

printf ("Input a date");
   if (month == 2) {
      month_mult = 28;
   } else if ((month % 2 == 0 && month <= 7) || (month%2 == 1 && month >= 8)) {
      month_mult = 30;
   } else {
      month_mult = 31;
   }
}
