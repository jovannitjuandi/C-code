#include<stdio.h>
#include <stdlib.h>

       int main()
       {
              FILE *fp;
              char ch;

              fp = fopen("tester.txt","r");            //Statement   1

              if(fp == NULL)
              {
                     printf("\nCan't open file or file doesn't exist.");
                     exit(0);
              }

              printf("\nData in file...\n");

              while((ch = fgetc(fp))!=EOF)           //Statement   2
                  printf("%c",ch);

              fclose(fp);
       }
