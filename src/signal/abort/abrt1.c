#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Emulates POSIX `abort(3)':
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/abort.html
 *
 * On Linux: since glibc 2.27, `abort(3)' terminates the process
 * without flushing streams.
 *
 */

void
abort (void)
{
  sigset_t set;
  struct sigaction act;

  sigaction (SIGABRT, NULL, &act);
  if (act.sa_handler == SIG_IGN)
    {
      act.sa_handler = SIG_DFL;
      sigaction (SIGABRT, &act, NULL);
    }

  if (act.sa_handler == SIG_DFL)
    {
      fflush (NULL);
    }

  sigfillset (&set);
  sigdelset (&set, SIGABRT);
  sigprocmask (SIG_SETMASK, &set, NULL);

  kill (getpid (), SIGABRT);

  fflush (NULL);

  act.sa_handler = SIG_DFL;
  sigaction (SIGABRT, &act, NULL);
  sigprocmask (SIG_SETMASK, &set, NULL);

  kill (getpid (), SIGABRT);

  /* should never reach here */
  exit (EXIT_FAILURE);
}
