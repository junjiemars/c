#include "../_lang_.h"
#include <stdio.h>
#include <stdlib.h>

#if (LINUX) || (DARWIN)
#include <unistd.h>
#endif

static void at_exit (void);

void
at_exit (void)
{
  printf ("----------\n");
  printf ("existing ...\n");
}

int
main (void)
{
  atexit (&at_exit);

  _exit (EXIT_SUCCESS);
}
