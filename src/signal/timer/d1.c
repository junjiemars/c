#include "_signal_.h"

/*
 * implementing software timers
 *
 * Reference:
 * http://www.kohala.com/start/libes.timers.txt
 *
 */

int
main (void)
{
  struct itimerval itval;

  if (getitimer (0, &itval) == -1)
    {
      perror (NULL);
    }
  exit (EXIT_SUCCESS);
}
