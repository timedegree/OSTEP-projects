#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    exit(0);
  } else {
    while (--argc > 0) {
      FILE *fp = fopen(*++argv, "r");
      if (fp == NULL) {
        printf("wcat: cannot open file\n");
        exit(1);
      }

      char buffer[100];
      while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
      }

      fclose(fp);
    }
  }

  return 0;
}
