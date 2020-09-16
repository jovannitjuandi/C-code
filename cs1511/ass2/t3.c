#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;

int main(void) {
    Node* link[5];
    for(int q = 0; q < 5; q++) {
        link[q] = malloc(sizeof(struct Node));
        link[q] = NULL;
    }
}
