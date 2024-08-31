#include "_stdio_.h"

#if MSVC
#define COMMAND_LS "dir"
#else
#define COMMAND_LS "ls"
#endif

#if (GCC) && (NM_HAVE_POPEN)
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#endif

int
main (void)
{
#if (NM_HAVE_POPEN)
  fprintf (stdout, "popen process i/o\n");
  fprintf (stdout, "--------------------\n");

  FILE *out = popen (COMMAND_LS, "r");
  if (!out)
    {
      return ferror (out);
    }

  char s[512];
  while (0 != fgets (s, sizeof (s), out))
    {
      printf ("%s", s);
    }
  if (feof (out))
    {
      fprintf (stdout, "!sucess\n");
    }
  else
    {
      fprintf (stderr, "!panic: ferror(out) = %d\n", ferror (out));
    }
  pclose (out);
#else
  fprintf (stdout, "!panic: popen fn no found\n");
#endif

  return 0;
}
