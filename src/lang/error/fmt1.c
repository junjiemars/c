#include "../_lang_.h"
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

#ifdef NM_HAVE_ERR_H
  warn ("!warn errno = %i", eval);
  err (EXIT_SUCCESS, "!err errno = %i", eval);
#else
  fprintf (stderr, "!warn errno = %i: %s\n", eval, strerror (eval));
  fprintf (stderr, "!err errno = %i: %s\n", eval, strerror (eval));
  exit (EXIT_SUCCESS);
#endif /* NM_HAVE_ERR_H */
}
