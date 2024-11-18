#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(int argc,char *argv[])
{
  if(argc == 1){
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }

  if(argc > 1){
    while(--argc > 0){
      FILE *fp = fopen(*++argv,"r");
      if(fp == NULL){
        printf("wunzip: cannot open file\n");
        exit(1);
      }
      
      int count;
      char chr;
    
      while(fread(&count,sizeof(int),1,fp) == 1 && fread(&chr,sizeof(char),1,fp) == 1){
        for(int i = 0; i < count; i++){
          printf("%c", chr);
        }
      }

      fclose(fp);
    }    
  }

  return 0;
}
