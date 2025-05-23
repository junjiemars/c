#include <_algo_.h>
#include "_hash_.h"

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
  int c;
  unsigned long h = 0;

  while (0 != (c = *str++))
    {
      h += c;
    }
  return h;
}
