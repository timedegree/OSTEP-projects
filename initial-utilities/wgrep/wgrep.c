#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  } else {
    argc--;
    char *searching = *++argv;

    while (--argc > 0) {
      FILE *fp = fopen(*++argv, "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }

      char *linebuffer = NULL;
      int *len = 0;
      while (getline(&linebuffer, &len, fp) == -1) {
        exit(1);
      }

      fclose(fp);
    }
  }

  return 0;
}
