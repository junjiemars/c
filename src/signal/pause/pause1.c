#include <_signal_.h>

/*
 * Emulates POSIX `pause(3)'.
 *
 */

int
pause (void)
{
  sigset_t nset;

  sigemptyset (&nset);
  sigsuspend (&nset);

  /* always returns -1 */
  return -1;
}
