#include "_flex_.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
  (void) (argc);
  (void) (argv);

  int i = 1234;
  doulbe d = 3.1415926;

  printf("i = %i\n", i);
  printf("d = %lf\n", d);

  return 0;
}
