#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

void print_prompt(bool flag){ //print prompt depend on flag
  char *prompt = "wish> ";
  
  if(flag){
    printf("%s",prompt); 
  }
}

void shell(FILE *fp,bool flag){
  char *line = NULL;
  size_t len;

  print_prompt(flag);
  while(getline(&line,&len,fp) != -1){
    line[strcspn(line,"\n")] = '\0';

    // get user input args
    char **command_args = NULL;
    size_t command_args_count = 0;
    char *tmp = NULL;
    char *line_cpy = line;
    while((tmp = strsep(&line_cpy," ")) != NULL){
      if(*tmp == '\0'){ //skip empty strings.
        continue;
      }
      
      command_args = realloc(command_args, (command_args_count+1)*sizeof(char *));
      if(command_args == NULL){
        fprintf(stderr,"wish: malloc failed\n");
        exit(1);
      }

      command_args[command_args_count] = strdup(tmp);
      if(command_args[command_args_count] == NULL){
        fprintf(stderr,"wish: malloc failed\n");
        exit(1);
      }
      command_args_count ++;
      free(tmp);
      tmp = NULL;
    }

    //excute command
    int rc=fork();
    if(rc < 0){
      fprintf(stderr,"wish: fork failed");  
    } else if(rc == 0){
      execv(command_args[0],command_args);
    } else{
      wait(NULL);
    }

    // free allocated memory 
    free(line);
    for(int i=0;i<command_args_count;i++){
      free(command_args[command_args_count]);
    }
    free(command_args);

    print_prompt(flag); 
  }

  exit(0);
}

int main(int argc,char *argv[]){
  if(argc == 1){ // if no args,get command from standard input
    FILE *fp = stdin;

    shell(fp,true);
  }

  if(argc == 2){ // else, get command from file
    FILE *fp = fopen(*++argv,"r");

    shell(fp,false);
  }
}
