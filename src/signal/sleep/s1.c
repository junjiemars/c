#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

/*
 * 1st: emulates POSIX `sleep(3)'.
 *
 */

unsigned int sleep (unsigned int);

static void on_sig_alrm (int);
static jmp_buf env_alrm;

unsigned int
sleep (unsigned int secs)
{
  void (*oact) (int);
  unsigned int wait;

  if ((oact = signal (SIGALRM, on_sig_alrm)) == SIG_ERR)
    {
      return secs;
    }

  wait = alarm (0);
  wait = (wait > 0 && wait < secs) ? wait : secs;

  if (setjmp (env_alrm) == 0)
    {
      alarm (wait);
      if (wait > 0)
        {
          pause ();
        }
    }
  alarm (0); /* always return 0 */

  signal (SIGALRM, oact);

  return (wait < secs) ? secs - wait : wait - secs;
}

void
on_sig_alrm (int signo)
{
  if (signo == SIGALRM)
    {
      longjmp (env_alrm, signo);
    }
}
