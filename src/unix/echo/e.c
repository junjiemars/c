#include "_unix_.h"
#include <stdio.h>
#include <string.h>

int
main (int argc, char **argv)
{
  int opt_n = 0;
  int opt_ind = 1;

  for (int i = opt_ind; i < argc; i++)
    {
      if (strcmp ("-n", argv[i]) == 0)
        {
           opt_n = 1;
           opt_ind = i+1;
           break;
        }
    }

  for (char **p = argv + opt_ind; *p != 0; p++)
    {
      char sp = (opt_ind == argc - 1) ? 0x0 : 0x20;
      fprintf (stdout, "%s%c", *p, sp);
    }

  if (opt_n == 0)
    {
      fprintf (stdout, "\n");
    }

  return 0;
}
