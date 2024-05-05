#include "_ld_.h"
#include <stdio.h>

/*
 * 1. with `-std' option using `__asm__` instead of `asm'.
 * 2. extended asm.
 * 3.
 *
 */

int
add (int a, int b)
{
  int rc = 0;
#if __x86_64__
  __asm__ volatile("add %1, %2\n\t" : "=r"(rc) : "r"(a), "0"(b));
#else
  rc = a + b;
#endif
  return rc;
}

int
main (void)
{
  int r = add (1, 2);
  printf ("%d\n", r);
  return 0;
}
