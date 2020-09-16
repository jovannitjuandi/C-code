#include <stdio.h>

int main(int argc, char* argv) {
    int max = 5;
    printf("%d\n", max);
    
    void change(int *c) {
        *c = 9;
    }
    
    change(&max);
    printf("%d\n", max);
}
