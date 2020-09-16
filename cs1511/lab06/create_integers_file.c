//made by Jovanni (z5213864)
//tutorial (Angus - Connor)


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
   if (argc < 4) {
        fprintf(stderr, "Not enough argument provided to %s\n", argv[0]);
        return 1;
    }

   FILE *outputStream;
   outputStream = fopen(argv[3], "w");
   
   if (outputStream == NULL) {
        fprintf(stderr, "Cannot open '%s', open fail\n", argv[3]);
        return 1;
    }

   int start = atoi(argv[1]);
   int end = atoi(argv[2]);

   while (start <= end) {
      fprintf (outputStream, "%d\n", start);
      start = start + 1;
   }
   fclose (outputStream);
   return 0;
}
