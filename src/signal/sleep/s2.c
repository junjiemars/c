#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>

/*
 * 1st: emulates POSIX `sleep(3)'.
 *
 */

unsigned int sleep (unsigned int);

static void on_sig_alrm (int);
static sigjmp_buf env_alrm;

unsigned int
sleep (unsigned int secs)
{
  sigset_t nset, oset;
  unsigned int wait;
  struct sigaction act, oact;

  if (sigprocmask (0, NULL, &oset) == -1)
    {
      return secs;
    }

  act.sa_handler = on_sig_alrm;
  act.sa_flags = 0;
  sigfillset (&act.sa_mask);
  sigdelset (&act.sa_mask, SIGALRM);
  if (sigaction (SIGALRM, &act, &oact) == -1)
    {
      return secs;
    }

  wait = alarm (0);
  wait = (wait > 0 && wait < secs) ? wait : secs;

  if (sigsetjmp (env_alrm, 1) == 0)
    {
      nset = act.sa_mask;
      alarm (wait);
      if (wait > 0)
        {
          sigsuspend (&nset);
        }
    }
  alarm (0); /* always return 0 */

  sigaction (SIGALRM, &oact, NULL);
  sigprocmask (SIG_SETMASK, &oset, NULL);

  return (wait < secs) ? secs - wait : wait - secs;
}

void
on_sig_alrm (int signo)
{
  if (signo == SIGALRM)
    {
      siglongjmp (env_alrm, signo);
    }
}
