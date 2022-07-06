#include "_signal_.h"


/*
 * 1. emulate sleep.
 * 2. there is race condition.
 * 3. alarm and pause had been obsolete.
 *
 */


static unsigned sleep1(unsigned nsecs);

static void on_sig_alrm(int signo);

int
main(void)
{
  sleep1(1);
  sleep1(2);
	sleep1(3);

  return 0;
}

void
on_sig_alrm(int signo)
{
  if (SIGALRM == signo)
    {
			printf("# %s\n", _str_(SIGALRM));
    }
}

unsigned
sleep1(unsigned nsecs)
{
  if (nsecs == 0)
    {
      return nsecs;
    }

  if (SIG_ERR == signal(SIGALRM, on_sig_alrm))
		{
			perror(NULL);
			return (nsecs);
		}

  alarm(nsecs);

  /* race condition: between alarm and pause */

  pause();

  return alarm(0);
}

