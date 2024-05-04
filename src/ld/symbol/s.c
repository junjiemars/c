#include "_ld_.h"
#include <stdio.h>

extern char **environ;

int
main (void)
{
  static char *ss = "Hello, symbol\n";
  printf ("%s\n", *environ);
  printf ("%s\n", ss);
  return 0;
}
