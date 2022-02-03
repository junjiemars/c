#include "_signal_.h"

/*
 * 1. emulate sleep.
 * 2. there is race condition.
 * 3. alarm and pause had been obsolete.
 *
 */


static unsigned sleep1(unsigned nsecs);

static void on_sig_alrm(int signo);


static void on_sig_alrm(int signo)
{
  if (SIGALRM == signo)
    {
      /* void */
    }
}

static unsigned
sleep1(unsigned nsecs)
{
  if (nsecs == 0)
    {
      return nsecs;
    }

  signal(SIGALRM, on_sig_alrm);

  alarm(nsecs);

  /* race condition: between alarm and pause */

  pause();

  return alarm(0);
}

int
main(void)
{
  sleep1(2);

  sleep1(4);

  return 0;
}
