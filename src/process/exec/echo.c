#include "_process_.h"

/*
 * Print command-line's arguments and `environ'.
 *
 */

int
main (int argc, char **argv)
{
  char **p;
  extern char **environ;

  for (int i = 0; i < argc; i++)
    {
      printf ("argv[%d]: %s\n", i, argv[i]);
    }

  for (p = environ; *p != 0; p++)
    {
      printf ("%s\n", *p);
    }

  exit (0);
}
