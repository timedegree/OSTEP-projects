#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep_line(FILE *fp, char *searching){
  char *linebuffer = NULL;
  size_t len = 0;

  while(getline(&linebuffer, &len, fp) != -1){
    char *substr = strstr(linebuffer, searching);
    
    if(substr != NULL){
      printf("%s",linebuffer);
    }

    free(linebuffer);
    linebuffer = NULL;
  }

  fclose(fp);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  if (argc == 2){  
    FILE *fp = stdin;
    char *searching = *++argv;
    
    grep_line(fp, searching);
  }

  if (argc > 2){
    argc--;
    char *searching = *++argv;
    
    while (--argc > 0) {
      FILE *fp = fopen(*++argv, "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      
      grep_line(fp, searching);
    }
  }

  return 0;
}
