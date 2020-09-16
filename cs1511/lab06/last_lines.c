#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_count(FILE *output);

int main (int argc, char *argv[]){
    
    if (argc < 2) {
        fprintf(stderr, "Not enough argument provided to %s\n", argv[0]);
        return 1;
    }
    
    FILE *output;
    output = fopen(argv[1], "r");
    
    if (output == NULL) {
        fprintf(stderr, "Cannot open '%s', open fail\n", argv[3]);
        return 1;
    }
    
    int lines = line_count (output);
    
    rewind(output);
    
    if (lines <= 10) {
        char ch = fgetc(output);
        while (ch != EOF) {
            printf("%c",ch);
            ch = fgetc(output);
        }
    } else {
        char ch = fgetc(output);
        int current_line = 0;
        while (ch != EOF) {
            if (current_line >= (lines - 10)) {
                printf("%c", ch);
            }
            if (ch == 10) {
                current_line = current_line + 1;
            }
            ch = fgetc(output);
        }
    }
}

int line_count(FILE *output) {
    char ch;
    int space = 0;
    
    ch = fgetc(output);
    while (ch != EOF) {
        if (ch == 10) {
            space = space + 1;
        }
        ch = fgetc(output);
    }
    return space;
}
