#include "_ld_.h"
#include <stdio.h>

int
add (int a, int b)
{
  int r = 0;
  __asm__("add %1, %2;" : "=r"(r) : "r"(a), "0"(b));
  return r;
}

int
main (void)
{
  int r = add (1, 2);
  printf ("%d\n", r);
  return 0;
}
