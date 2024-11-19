#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>

void reverse(FILE *input, FILE *output){
  char *linebuffer = NULL;
  size_t len = 0;
  char **line_list = NULL;
  int line_count = 0;
  
  while(getline(&linebuffer,&len,input) != -1){
    char **tmp = realloc(line_list, (line_count+1)*sizeof(char *));
    if(tmp == NULL){
      fprintf(stderr, "reverse: malloc failed\n");
      free(linebuffer);
      for(int i = 0; i < line_count; i++){
        free(line_list[i]);
      }
      free(line_list);
      exit(1);
    }
    line_list = tmp;

    line_list[line_count] = strdup(linebuffer);
    if(line_list[line_count] == NULL){
      fprintf(stderr, "reverse: malloc failed\n");
      free(linebuffer);
      for(int i = 0; i < line_count; i++){
        free(line_list[i]);
      }
      free(line_list);
      exit(1);     
    }

    ++line_count;
  }

  for(int i = line_count-1; i>=0; i--)
  {
    fprintf(output,"%s",line_list[i]);
    free(line_list[i]);
  }

  free(linebuffer);
  free(line_list);
}

int main(int argc, char *argv[]){
  if(argc == 1){
    reverse(stdin, stdout);
  } else if(argc == 2){
    char *input = *++argv;
    FILE *input_fp = fopen(input,"r");
    if(input_fp == NULL){
      fprintf(stderr, "reverse: cannot open file '%s'\n",input);
      exit(1);
    }
    
    reverse(input_fp, stdout);
  } else if(argc == 3){
    char *input = *++argv;
    char *output = *++argv;

    struct stat input_stat, output_stat;
    if (stat(input, &input_stat) == 0 && stat(output, &output_stat) == 0) {
        if (input_stat.st_dev == output_stat.st_dev && input_stat.st_ino == output_stat.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
    }

    FILE *input_fp = fopen(input, "r");
    FILE *output_fp = fopen(output, "w");
    if(input_fp == NULL){
      fprintf(stderr, "reverse: cannot open file '%s'\n",input);
      exit(1);
    }
    if(output_fp == NULL){
      fprintf(stderr, "reverse: cannot open file '%s'\n",output);
      exit(1);
    }

    reverse(input_fp, output_fp);
  } else {
    fprintf(stderr, "usage: reverse <input> <output>\n");
    exit(1);
  }

  return 0;
}
