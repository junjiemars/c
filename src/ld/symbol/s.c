#include "_ld_.h"
#include <stdio.h>

extern char **environ;

int
main (void)
{
  for (char **p = environ; *p != 0; p++)
    {
      printf ("%s\n", *p);
    }
}
