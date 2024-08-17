#include "_lang_.h"
#include <err.h>

int
main (int argc, char **argv)
{
  int eval;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <errno>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  sscanf (argv[1], "%i", &eval);

  errno = eval;
  warn (0, "errno= %i", eval);
  err (EXIT_SUCCESS, "errno = %i", eval);
}
