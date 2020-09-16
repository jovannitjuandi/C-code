// COMP2521 20T2 Assignment 1
// tw.c ... compute top N most frequent words in file F
// Usage: ./tw [Nwords] File

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "Dict.h"
#include "WFreq.h"
#include "stemmer.h"

#define STOPWORDS "stopwords"
#define MAXLINE 1000
#define MAXWORD 100

#define STARTING "*** START OF"
#define ENDING   "*** END OF"

#define isWordChar(c) (isalnum(c) || (c) == '\'' || (c) == '-')

int main( int argc, char *argv[])
{
////////////////////////////////////////////////////////////////////////
    // DECLARE VARIABLES

    FILE  *in;         // currently open file
    Dict   stopwords;  // dictionary of stopwords
    Dict   wfreqs;     // dictionary of words from book
    WFreq *results;    // array of top N (word,freq) pairs
                       // (dynamically allocated)

    char *fileName;    // name of file containing book text
    int   nWords;      // number of top frequency words to show

    char   line[MAXLINE];  // current input line
    char   word[MAXWORD];  // current word

////////////////////////////////////////////////////////////////////////
    // PROCESS COMMAND LINE ARGUMENTS
    switch (argc) {
    case 2:
        nWords = 10;
        fileName = argv[1];
      break;
    case 3:
        nWords = atoi(argv[1]);
        if (nWords < 10) nWords = 10;
        fileName = argv[2];
        break;
    default:
        fprintf(stderr,"Usage: %s [Nwords] File\n", argv[0]);
        exit(EXIT_FAILURE);
    }

////////////////////////////////////////////////////////////////////////
    // BUILD STOPWORD DICTIONARY
    stopwords = newDict();

    in = fopen(STOPWORDS, "r");
    if (in == NULL) {
        fprintf(stderr, "Can't open stopwords\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, MAXLINE, in) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        DictInsert(stopwords, line);
    }

////////////////////////////////////////////////////////////////////////
    // SCAN FILE TO START OF TEXT
    in = fopen(fileName, "r");
    if (in == NULL) {
        fprintf(stderr, "Can't open %s\n",fileName);
        exit(EXIT_FAILURE);
    }
    
    // Iterate through everyline untill STARTING line is found
    while (fgets(line, MAXLINE, in) != NULL) 
        if (strstr(line, STARTING) != NULL) break;
    
    // Check where iteration stops
    // If the next line is NULL then nothing was found / empty text
    // If the next line exists then it is the first line
    if (fgets(line, MAXLINE, in) == NULL) {
        fprintf(stderr, "Not a Project Gutenberg book\n");
        exit(EXIT_FAILURE);
    } 

////////////////////////////////////////////////////////////////////////
    // SCAN FILE READING WORDS AND ACCUMULATING COUNTS
    
    // note: line now contains the first line
    memset(word, 0, strlen(word));
    int i = 0, j = 0;
    wfreqs = newDict();

    // processing the first line
    while (i < strlen(line)) {
        if (isWordChar(line[i]) == 1) {
            word[j] = tolower(line[i]);
            j++;
        } else {
            word[j] = '\0';
            j= 0;
            if ((strlen(word) > 1) & (DictFind(stopwords, word) == NULL)) {
                int ans = stem(word, 0, strlen(word)-1);
                word[ans + 1] = '\0';
                DictInsert(wfreqs, word);
            }
            memset(word, 0, strlen(word));
        } 
        i++;
    }

    // processing to the ENDING line
    while (fgets(line, MAXLINE, in) != NULL) {
        if (strstr(line, ENDING) != NULL) break;
        i = 0;
        memset(word, 0, strlen(word));
        while (i < strlen(line)) {
            if (isWordChar(line[i]) == 1) {
                word[j] = tolower(line[i]);
                j++;
            } else {
                word[j] = '\0';
                j= 0;
                if ((strlen(word) > 1) & (DictFind(stopwords, word) == NULL)) {
                    int ans = stem(word, 0, strlen(word)-1);
                    word[ans + 1] = '\0';
                    DictInsert(wfreqs, word);
                }
                memset(word, 0, strlen(word));
            }
            i++;
        }
    }

////////////////////////////////////////////////////////////////////////
    // COMPUTE AND DISPLAY THE TOP N WORDS
    results = (WFreq *) malloc(nWords*sizeof(WFreq));
    findTopN(wfreqs, results, nWords);
   
    // displaying result in proper format
    for (int count = 0; count < nWords; count++)
        printf("%7d %s\n", results[count].freq, results[count].word);

////////////////////////////////////////////////////////////////////////
   return EXIT_SUCCESS;
}
