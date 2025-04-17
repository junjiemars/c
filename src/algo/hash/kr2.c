#include "_hash_.h"
#include <_algo_.h>

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
  unsigned long h;
  for (h = 0; *str; str++)
    {
      h = *str + 31 * h;
    }
  return h % 1024;
}
