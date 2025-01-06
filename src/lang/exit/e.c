#include "../_lang_.h"
#include <stdio.h>
#include <stdlib.h>

static void at_exit_first (void);
static void at_exit_second (void);

int
main (void)
{
  if (atexit (&at_exit_first))
    {
      perror ("1st");
      return 1;
    }

  if (atexit (&at_exit_second))
    {
      perror ("2nd");
      return 1;
    }

  if (atexit (at_exit_second))
    {
      perror ("3rd");
      return 1;
    }

  printf ("calling exit() ...\n");
  exit (EXIT_SUCCESS);
}

void
at_exit_first (void)
{
  printf ("----------\n");
  printf ("existing first ...\n");
}

void
at_exit_second (void)
{
  printf ("----------\n");
  printf ("existing second ...\n");
}
