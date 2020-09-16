//made by Jovanni (z5213864)
//tutorial (Angus - Connor)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

   int space = 0;
   int nom = 0;
   char ch;

   FILE *output;
   output = fopen(argv[1], "r");
   //while (fgetc(outputStream) != EOF) {
      //fgets (line, 4096, stdin);
      //printf ("%s", line);
   //}
   
   while((ch = fgetc(output)) && ch !=EOF) {         
      printf("%c",ch);
      if (ch == 10) {
         space = space + 1;
      }
   }
/*ch = fgetc(output);
 printf("%c",ch);
while(ch !=EOF) {    
      ch = fgetc(output);     
      
      if (ch == 10) {
         space = space + 1;
      }
}*/
   //while (fgetc(outputStream) != EOF) {
      //char ch = fgetc(outputStream);
      //nom = fgetc (outputStream);
      //if (nom == 10) {
         //space = space + 1;
      //}
      //printf ("%d" , nom);
      //nom = fgetc(outputStream);
      //printf ("%d ", nom);
      //printf ("%c", ch);  
      //putchar (fgetc (outputStream));
      //putchar(getchar());
      //fgets (line, 4096, stdin);
      //printf ("%s", line);
   //}
   printf ("\n%d\n" , space);   
}
