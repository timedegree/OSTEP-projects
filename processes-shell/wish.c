#include <stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/wait.h>

char **paths = NULL;
size_t paths_num = 0;
pid_t *child_pids = NULL;
size_t child_num = 0;

void error(){
  char error_message[30] = "An error has occurred\n";
  write(STDERR_FILENO, error_message, strlen(error_message));
}

void print_prompt(bool flag){ // print prompt depend on flag
  char *prompt = "wish> ";
  
  if(flag){
    printf("%s", prompt); 
  }
}

void add_path(char *new_path) {
  if(realpath(new_path, NULL) == NULL){
    error();
    return;
  }

  for (size_t i = 0; i < paths_num; i++) { // path exists
    if (strcmp(paths[i], new_path) == 0) {
        return;    
    }
  }

  paths_num++;
  paths = realloc(paths, paths_num * sizeof(char *));
  if (paths == NULL) {
    error();
    exit(1);
  }

  paths[paths_num - 1] = strdup(new_path);
  if (paths[paths_num - 1] == NULL) {
    error();
    exit(1);
  }
}

int handle_redirection(command_args, start) {

}

void excute_command(char **command_args, size_t command_args_count){
  if(command_args_count == 0) return; // no command to excute
  
  for(size_t i=0;i<command_args_count;i++){
    // built-in command excute
    if(!strcmp(command_args[i],"exit")){
      if(i+1 == command_args_count || command_args[i+1] == NULL){
        exit(0);
      } else{
        i++;
        error();
      }
    } else if(!strcmp(command_args[i],"cd")){
      if(chdir(command_args[++i])){
        error();
      }
      while(command_args[i] != NULL) {
        i++;
      }
      i++;
    } else if(!strcmp(command_args[i],"path")){
      
    }
    else{ // external command excute
      pid_t pid = fork();
      child_pids = realloc(child_pids,++child_num);
      child_pids[child_num-1] = pid;

      if(pid == -1){
        error();
        exit(1);
      } else if(pid == 0){ // child
        if(handle_redirection(command_args,i)) {
          for(size_t j = 0; j<paths_num;j++){
            char *command = malloc((strlen(paths[j])+1+strlen(command_args[i]))*sizeof(char));
            strcpy(command,paths[j]);
            strcat(command,"/");
            strcat(command,command_args[i]);
            if(!access(command,X_OK)) {
              execv(command,command_args+i);
            }
          }
          error();
          exit(1);
        } 
      } else{ // parent

      }
    }
  }
  
}

void shell(FILE *fp, bool flag){
  char *line = NULL;
  size_t len = 0;

  print_prompt(flag);
  while(getline(&line,&len,fp) != -1){
    line[strcspn(line,"\n")] = '\0';

    // handle & > |
    char *processed_line = NULL;
    size_t processed_len = 0;
    for(size_t i=0;i<len;i++)  {
      char tmp_char = line[i];
      if(tmp_char == '&' || tmp_char == '>' || tmp_char == '|') {
        processed_line = realloc(processed_line, processed_len+3) ;
        if(processed_line == NULL) {
          error();
          exit(1);
        }
        
        processed_line[processed_len++] = ' ';
        processed_line[processed_len++] = tmp_char;
        processed_line[processed_len++] = ' ';
      } else{
        processed_line = realloc(processed_line, processed_len+1) ;
        if(processed_line == NULL){
          error();
          exit(1);
        }

        processed_line[processed_len++] = tmp_char;
      }
    }
    processed_line = realloc(processed_line, processed_len+1);
    if(processed_line == NULL) {
      error();
      exit(1);
    }
    processed_line[processed_len] = '\0';

    free(line);
    line = processed_line;

    // get user input args
    char **command_args = NULL;
    size_t command_args_count = 0;
    char *tmp = NULL;
    char *line_cpy = line;
    while((tmp = strsep(&line_cpy," ")) != NULL){
      if(*tmp == '\0')   continue; // skip empty strings 
      
      command_args = realloc(command_args, (command_args_count+1)*sizeof(char *));
      if(command_args == NULL) {
        error();
        exit(1);
      }
      
      // change & to NULL
      if(!strcmp(tmp,"&")) {
        command_args[command_args_count] = NULL;
      } else{
        command_args[command_args_count] = strdup(tmp);
      }
      if(command_args[command_args_count] == NULL) {
        error();
        exit(1);
      }

      command_args_count++;
      free(tmp);
      tmp = NULL;
    }

    // excute command
    excute_command(command_args,command_args_count);

    // free allocated memory 
    free(line);
    for(size_t i=0;i<command_args_count;i++){
      free(command_args[i]);
    }
    free(command_args);

    print_prompt(flag); 
  }
  
  free(line);
  exit(0);
}

void initialize(){
  paths_num = 1;
  paths = malloc(paths_num * sizeof(char *));
  if(paths == NULL) 
  {
    error();
    exit(1);
  }

  paths[0] = strdup("/bin");
  if(paths[0] == NULL) {
    error();
    exit(1);
  }
}


int main(int argc, char *argv[]){
  initialize();

  if(argc == 1){ // if no args,get command from standard input
    shell(stdin,true);
  } else if(argc == 2){ // else, get command from file
    FILE *fp = fopen(*++argv,"r");
    if(fp == NULL) {
      error();
      exit(1);
    }

    shell(fp,false);
  } else{
    error();
    exit(1);
  } 
}
