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
  const char *ss;
  unsigned long h;

  if (argc > 1)
    {
      ss = argv[1];
      h = hash (ss);
      print_hash ("djb2 hash", ss, h);
    }
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
