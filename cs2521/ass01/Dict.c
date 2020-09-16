// COMP2521 20T2 Assignment 1
// Dict.c ... implementsation of Dictionary ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dict.h"
#include "WFreq.h"

#define MAXWORD 100

////////////////////////////////////////////////////////////////////////
// PROVIDED DATA STRUCTURE
typedef struct _DictNode *Link;

typedef struct  _DictNode {
    WFreq  *data;
    Link   left;
    Link   right;
    int    height;
} DictNode;

typedef struct _DictRep {
    Link tree;
} DictRep;

////////////////////////////////////////////////////////////////////////
// ADDITIONAL DATA STRUCTURE
typedef struct _WFreqNode *WFLink;

typedef struct _WFreqNode {
    WFreq *data;
    WFLink next; 
} WFNode;

////////////////////////////////////////////////////////////////////////
// ADDITIONAL FUNCTION PROTOTYPE

// tree creation helper functions
static WFreq *newWF();
static Link newLink(char *w);
static Link insertWord(Link l, char *w);
static Link rotateLeft(Link n);
static Link rotateRight(Link n);

// WFreq linkedList helper functions
static WFLink newWFLink();
static WFLink addWFLink(WFLink w, WFreq *n);
void printLinked(WFLink w);

// converts a tree into a linkedList
WFLink addToList(WFLink w, Link l);

// more helper functions
int setHeight(Link n);
static int max(int a, int b);
static int height(Link l);

// further helper algorithms
void TreeShow(Dict d);
void mergeSort(WFLink *w);

////////////////////////////////////////////////////////////////////////
// PROVIDED FUNCTIONS
// create new empty Dictionary
Dict newDict()
{
    Dict d = malloc(sizeof(*d));
    if (d == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    d->tree = NULL;
    return d;
}

// insert new word into Dictionary
// return pointer to the (word,freq) pair for that word
WFreq *DictInsert(Dict d, char *w)
{
    d->tree = insertWord(d->tree, w);
    WFreq *new = DictFind(d, w);

    return new;
}

// find Word in Dictionary
// return pointer to (word,freq) pair, if found
// otherwise return NULL
WFreq *DictFind(Dict d, char *w)
{
    if (d->tree == NULL) return NULL;
    
    Link l = d->tree;
    while (strcmp(w, l->data->word) != 0) {
        if (l->data->word != NULL) {
            if (strcmp(w, l->data->word) > 0) l = l->right;
            else l = l->left;
        }

        if (l == NULL) return NULL;
    }
    return l->data;
}

// find top N frequently occurring words in Dict
// input: Dictionary, array of WFreqs, size of array
// returns: #WFreqs in array, modified array
int findTopN(Dict d, WFreq *wfs, int n)
{
    // allocate memory for wfs
    // move everything into an WFreq linkedlist
    WFLink fullDict = newWFLink();
    fullDict = addToList(fullDict, d->tree);

    // sort the linked list
    mergeSort(&fullDict);

    // return topN
    int i = 0;
    WFLink l = fullDict;
    while (i < n && l != NULL) {
        wfs[i] = *l->data;

        l = l->next;
        i++;
    }

    return n;
}

// print a dictionary
void showDict(Dict d)
{
    TreeShow(d);
    return;
}

////////////////////////////////////////////////////////////////////////
// ADDITIONAL FUNCTION IMPLEMENTATIONS
static WFreq *newWF() {
    WFreq *new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    new->word = NULL;
    new->freq = 0;
    return new;
}

static Link newLink(char *w) {
    Link l = malloc(sizeof(*l));
    if (l == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    char *str = (char*) malloc(MAXWORD*sizeof(char));
    if (str == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    
    WFreq *new = newWF();
    strcpy(str, w);
    new->word = str;
    new->freq = 0;
    
    l->data = new;
    l->height = 0;
    l->left = NULL;
    l->right = NULL;
    
    return l;
}

static Link insertWord(Link l, char *w) {
    if (l == NULL) {
        Link new = newLink(w);
        new->data->freq++;
        return new;
    }

    // insert recursively
    int cmp = strcmp(w, l->data->word);
    if (cmp < 0) {
        l->left = insertWord(l->left, w);
    } else if (cmp > 0) {
        l->right = insertWord(l->right, w);
    } else { // (cmp == 0)
        l->data->freq++;
        return l;
    }
    
    // insertion done
    // correct the height of the current subtree
    l->height = 1 + max(height(l->left), height(l->right));
    
    int Lheight = height(l->left);
    int Rheight = height(l->right);
    
    if ((Lheight - Rheight) > 1) {
        if (strcmp(w, l->left->data->word) > 0) {
            l->left = rotateLeft(l->left);
        }
        l = rotateRight(l);
    } else if ((Rheight - Lheight) > 1) {
        if (strcmp(w, l->right->data->word) < 0) {
            l->right = rotateRight(l->right);
        }
        l = rotateLeft(l);
    }
    
    return l;
}

static Link rotateLeft(Link n) {
    if (n == NULL || n->right == NULL) return n;
    
    Link r = n->right;
    n->right = r->left;
    r->left = n;
    
    setHeight(r);
    return r;
}

static Link rotateRight(Link n) {
    if (n == NULL || n->left == NULL) return n;
    
    Link l = n->left;
    n->left = l->right;
    l->right = n;
    
    setHeight(l);
    return l;
}

static WFLink newWFLink() {
    WFLink new = malloc(sizeof(*new));
    if (new == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    
    WFreq *n = newWF();
    new->data = n;
    new->next = NULL;
    
    return new;
}

static WFLink addWFLink(WFLink head, WFreq *n) {
    WFLink new = newWFLink();
    new->data = n;
    new->next = head;
    head = new;
    
    return head;
}

void printLinked(WFLink w) {
    while (w != NULL) {
        printf("%s -> ", w->data->word);    
        w = w->next;        
    }

    printf("END\n");
}

WFLink addToList(WFLink w, Link l) {
    if (l == NULL) return w;
    
    w = addToList(w, l->left);
    w = addWFLink(w, l->data);
    w = addToList(w, l->right);
    
    return w;
}

int setHeight(Link n) {
    if (n == NULL) {
        return -1;
    } else {
        n->height = max(setHeight(n->left), setHeight(n->right)) + 1;
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

static int height(Link l) {
    if (l == NULL) {
        return -1;
    } else {
        return l->height;
    }
}
   
////////////////////////////////////////////////////////////////////////
// SHOW TREE STRUCTURE
typedef unsigned long long uint64;
static void doShow(Link n, int level, uint64 arms);

void TreeShow(Dict d) {
    if (d->tree != NULL && d->tree->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(d->tree, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Link n, int level, uint64 arms) {
    if (n == NULL) return;

    printf("%s [%d]", n->data->word, n->data->freq);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// MERGE SORT ALGORITHM
void splitList(WFLink head, WFLink *p1, WFLink *p2);
WFLink mergeList(WFLink p1, WFLink p2);

void mergeSort(WFLink *w) {
    WFLink head = *w;
    WFLink p1 = NULL;
    WFLink p2 = NULL;
    
    // BASE CASE
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    
    // SPLITTING
    splitList(head, &p1, &p2);
    
    mergeSort(&p1);
    mergeSort(&p2);
    
    *w = mergeList(p1,p2);
}
void splitList(WFLink head, WFLink *p1, WFLink *p2) {
    
    WFLink fast, slow;
    
    if ((head == NULL) || (head->next == NULL)) {
        *p1 = head;
        *p2 = NULL;
    } else {
        slow = head;
        fast = head->next;
        while (fast != NULL) {
            // fast moves twice faster so when fast reaches 
            // the end, slow will be in the middle
            fast = fast->next;
            if (fast != NULL) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        *p1 = head;
        *p2 = slow->next;
        slow->next = NULL;
    }
}

WFLink mergeList(WFLink p1, WFLink p2) {
    WFLink merged = NULL;
    
    // BASE CASE
    if (p1 == NULL) {
        return p2;
    } else if (p2 == NULL) {
        return p1;
    }
    
    if (p1->data->freq > p2->data->freq) {
        merged = p1;
        merged->next = mergeList(p1->next, p2);
    } else {
        merged = p2;
        merged->next = mergeList(p1, p2->next);
    }
    return merged;
}
