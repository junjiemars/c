#include "_signal_.h"


/*
 * Elmulates POSIX `abort(3)'.
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/abort.html
 *
 * On Linux: since glibc 2.27, `abort(3)' terminates the process
 * without flushing streams.
 *
 */


void
abort(void)
{
  sigset_t          set;
  struct sigaction  act;

  if (sigaction(SIGABRT, NULL, &act) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (act.sa_handler == SIG_IGN)
    {
      act.sa_handler = SIG_DFL;
      sigaction(SIGABRT, &act, NULL);
    }

  if (act.sa_handler == SIG_DFL)
    {
      fflush(NULL);
    }

  sigfillset(&set);
  sigdelset(&set, SIGABRT);
  sigprocmask(SIG_SETMASK, &set, NULL);

  raise(SIGABRT);

  fflush(NULL);

  act.sa_handler = SIG_DFL;
  sigaction(SIGABRT, &act, NULL);
  sigprocmask(SIG_SETMASK, &set, NULL);

  raise(SIGABRT);

  exit(EXIT_FAILURE);
}
