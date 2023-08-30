#include "_unix_.h"
#include <stdio.h>


int
main (int argc, char **argv)
{
  int opt_n = 0;
  int opt_ind = 1;

  if (argc > 1)
    {
      opt_n = *argv[1] == '-' && *(argv[1]+1) == 'n';
      opt_ind += opt_n;
    }
  else
    {
      fprintf(stdout, "\n");
      return 0;
    }

  for (int i = opt_ind; i < argc; i++)
    {
      char *s = i+1 < argc ? " " : opt_n == 0 ? "\n" : "";
      fprintf (stdout, "%s%s", argv[i], s);
    }

  return 0;
}
