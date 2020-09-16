#include <stdio.h>
enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun}; 
  
int main() 
{ 
    enum week day; 
    day = Wed; 
    printf("%d",day); 
    // HOW TO REVERSE THE PROCESS ?? printf ("%s\n", week day);
    return 0; 
}  
