#include "_signal_.h"
#include <signal.h>

/*
 * Emulate `signal(3)'.
 *
 */

typedef void (sigfn) (int);

sigfn *
signal (int signo, sigfn *fn)
{
  struct sigaction act, oact;

  act.sa_handler = fn;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;

  if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
      act.sa_flags |= SA_INTERRUPT;
#endif
    }
  else
    {
      act.sa_flags |= SA_RESTART;
    }

  if (sigaction (signo, &act, &oact) == -1)
    {
      return SIG_ERR;
    }
  return oact.sa_handler;
}
