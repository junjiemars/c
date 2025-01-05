#include "../_signal_.h"
#include <setjmp.h>

/*
 * 1st: emulates POSIX `sleep(3)'.
 *
 */

unsigned int sleep (unsigned int);

static void on_sig_alrm (int);

unsigned int
sleep (unsigned int secs)
{
  sigset_t nset, oset, wset;
  unsigned int wait;
  struct sigaction act, oact;

  wait = alarm (0);
  wait = (wait > 0 && wait < secs) ? wait : secs;

  if (wait > 0)
    {
      act.sa_handler = on_sig_alrm;
      act.sa_flags = 0;
      sigemptyset (&act.sa_mask);
      if (sigaction (SIGALRM, &act, &oact) == -1)
        {
          return secs;
        }

      /* block SIGALRM */
      sigemptyset (&nset);
      sigaddset (&nset, SIGALRM);
      if (sigprocmask (SIG_BLOCK, &nset, &oset) == -1)
        {
          return secs;
        }

      wset = oset;
      sigdelset (&wset, SIGALRM);

      alarm (wait);

      /* wait for SIGALRM */
      sigsuspend (&wset);

      /* restore signal action and mask */
      sigaction (SIGALRM, &oact, NULL);
      sigprocmask (SIG_SETMASK, &oset, NULL);
    }

  return (wait < secs) ? secs - wait : wait - secs;
}

void
on_sig_alrm (int signo)
{
  (void)signo;
}
