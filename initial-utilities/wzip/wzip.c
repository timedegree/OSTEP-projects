#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char *argv[])
{
  if(argc == 1){
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }
  
  if(argc > 1){
    int count = 1;

    while(--argc >0){
      FILE *fp = fopen(*++argv,"r");
      if(fp == NULL){
        printf("wzip: cannot open file\n");
        exit(1);
      }

      char prev = fgetc(fp);
      if(prev == EOF){
        fclose(fp);
        continue;
      }
      char curr;
      
      while((curr = fgetc(fp)) != EOF){
        if(curr != prev){
          fwrite(&count,sizeof(int),1,stdout);
          fwrite(&prev,sizeof(char),1,stdout);
          count = 1;
          prev = curr;
        }
        else{
          count++;
        }
      }
      
      if(argc == 1){
        fwrite(&count,sizeof(int),1,stdout);
        fwrite(&prev,sizeof(char),1,stdout);
      }
      fclose(fp);
    }
  }
}
