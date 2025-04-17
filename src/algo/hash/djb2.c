#include <_algo_.h>
#include "_hash_.h"

/*
 * Written by Daniel J. Bernstein (aka. djb)
 *
 * https://en.wikipedia.org/wiki/Daniel_J._Bernstein
 * https://theartincode.stanis.me/008-djb2/
 */

int
main (int argc, char **argv)
{
  FILE *in = (argc > 1) ? fopen (argv[1], "r") : stdin;
  test_hash (in);
  return 0;
}

unsigned long
hash (const char *str)
{
  unsigned long h = 5381;
  int c;
  while (0 != (c = *str++))
    {
      h = ((h << 5) + h) + c; /* h * 33 + c */
    }
  return h;
}
