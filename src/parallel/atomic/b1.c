#include "_parallel_.h"
#include <stdatomic.h>
#include <stdio.h>

int
main (void)
{
  atomic_int x;

  atomic_init (&x, 0x1234);
  printf ("%#0x\n", x);

  atomic_fetch_add (&x, 1);
  printf ("%#0x\n", x);

  atomic_fetch_add (&x, 2);
  printf ("%#0x\n", x);

  return 0;
}
