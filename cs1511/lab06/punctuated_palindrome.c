#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096

int main (int argc, char *argv[]) {
    char line [MAX_LINE];
    char refined [MAX_LINE];
    
    printf ("Enter a string: ");
    fgets(line, MAX_LINE, stdin);
    int length = strlen (line);
    
    int c = 0;
    int index = 0;
    
    while (c < length) {
        if (isalpha(line[c]) != 0) {
            refined[index] = tolower(line[c]);
            index = index + 1;
        }
        c = c + 1;
    }
    
    int cur_length = index - 1;
    index = 0;
    int half = cur_length/2;
    c = 0;
    int stat = 1;
    
    while (c <= half) {
        if (tolower(refined[c]) != tolower(refined[cur_length - c])) {
            stat = 0;
            c = half;
        }
        c = c + 1;
    }
      
    if (stat == 0) {
      printf ("String is not a palindrome\n");
    } else {
      printf ("String is a palindrome\n");
    }
}
