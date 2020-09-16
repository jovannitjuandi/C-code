#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int         data;
};



struct node *create_node(int val, struct node *m){

    struct node *n = malloc(sizeof(struct node));
    if(n == NULL) {
        fprintf(stderr,"Error...\n");
    }
    
    n->data = val; 
    n->next = m;

    return n;
}

int sum( struct node *head){
    int sum = 0; 

    struct node *p = head; 
    while( p != NULL) {

        sum = sum + p->data;
        
        p = p->next; 
    }

    return sum;
}


struct node * find(struct node *head, int val){

    struct node *p; 
    p = head; 

    while( p != NULL) {

        if(p->data == val){
            return p; 
        }
        
        p = p->next; 
    }

    return NULL;
}


struct node * find2(struct node *head, int val){

    for(struct node *p=head; p != NULL; p = p->next){
        if(p->data == val){
            return p; 
        }
    }
    
    return NULL;
}


int main(int argc, char *argv[]) {

    struct node *h = create_node(55, NULL);
    h = create_node(37, h);
    h = create_node(87, h);    
    h = create_node(56, h);
    h = create_node(16, h);

    
    struct node *p = h; 
    while( p != NULL) {
        printf("data is %d\n", p->data);
        p = p->next; 
    }
    
    
   int my_sum = sum(h);     
   
   printf("Sum is %d\n", my_sum);
    
   int v = 1212; 
   struct node *f1 = find2(h, v);
   if(f1 != NULL) {
        printf("Found %d,  f1->data : %d \n", v, f1->data);
   }
   else {
        printf("NOT Found : %d \n", v);  
   }

    
}



