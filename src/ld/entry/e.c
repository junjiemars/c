#include "_ld_.h"
#include <string.h>
#include <unistd.h>

/*
 * 1. Using `exit' instead of using `return'.
 *
 * 2. Can't get `argc' and `argv' when compile with `-nostartfiles'.
 *
 * 3. Can access `environ'.
 *
 * 4. Access `fprintf' on Linux failed.
 *
 */

#define ss " "

int
main1 (int argc, char **argv)
{
  for (int i = 0; i < argc; i++)
    {
      write (STDOUT_FILENO, argv[i], strlen (argv[i]));
      write (STDOUT_FILENO, ss, sizeof (ss) - 1);
    }
  return 0;
}
