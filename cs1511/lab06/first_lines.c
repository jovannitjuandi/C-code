//made by Jovanni (z5213864)
//tutorial (Angus - Connor)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
   
   char ch;
   int space = 0;

   FILE *output;
   
   if (argc == 2) {
      output = fopen(argv[1], "r");
      ch = fgetc(output);
      if (output == NULL) {
         fprintf(stderr, "%s: open of '%s' failed\n", argv[0], argv[1]);
         return 1;
      }
      while(ch !=EOF && space < 10) {
         printf("%c",ch);
         if (ch == 10) {
            space = space + 1;
         }
         ch = fgetc(output);
      }
   
   } else if (argc == 4) {
      output = fopen(argv[3] , "r");
      if (output == NULL) {
         fprintf(stderr, "%s: open of '%s' failed\n", argv[0], argv[3]);
         return 1;
      }
      while((ch = fgetc(output)) && ch !=EOF && space < atoi(argv[2])) {
         printf("%c",ch);
         if (ch == 10) {
            space = space + 1;
         }
      }
   
   } else {
         fprintf(stderr, "Not enough argument provided to %s\n", argv[0]);
         return 1;
   }
fclose (output);
return 0;
}
