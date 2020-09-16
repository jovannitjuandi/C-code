// Simple example of file creation
// creates file "andrew.txt" containing 1 line ("Andrew rules!")
// Andrew Taylor - andrewt@unsw.edu.au
// 8/3/18

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *outputStream;

    outputStream = fopen("jov.txt", "b");
    if (outputStream == NULL) {
        fprintf(stderr, "%s: open of '%s' failed\n", argv[0], "andrew.txt");
        return 1;
    }

    fprintf(outputStream, "Andrew rules!\n");
    fclose(outputStream);

    return 0;
}
