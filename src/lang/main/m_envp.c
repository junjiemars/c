#include <_lang_.h>
#include <stdio.h>

int
main(int argc, char **argv, char **envp) {
  _unused_(argc);
  _unused_(argv);

  char **p = envp;
  printf("char **envp ...\n----------\n");
  while (*p) {
    printf("%s\n", *p++);
  }

  return 0;
}

