#include "_signal_.h"


/*
 * 1. emulate sleep.
 * 2. there is race condition.
 * 3. alarm and pause had been obsolete.
 *
 */


static unsigned sleep1(unsigned int);

static void on_sig_alrm(int signo);
static void race(long);

static long  N  =  0;

int
main(int argc, char **argv)
{
  if (argc > 1)
    {
      N = atol(argv[1]);
    }

  sleep1(1);
  sleep1(1);
  sleep1(1);

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
  race(N);

  pause();

  return alarm(0);
}

void
race(long n)
{
  _unused_(volatile double  d)  =  0;

  for (long i = 0; i < n; i++)
    {
      d += rand() * n;
    }
}
