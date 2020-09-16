#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *reverse (char *str);
char *tail (char *str);

int main(void) {
    
    char *p = "hello";
    printf("%s\n", p[2..3]);
    
    return 0; 
}

char *tail (char *str) {
    //return str[1..(strlen(str)-1)];
    return "test";
}

