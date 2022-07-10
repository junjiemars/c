#include "_signal_.h"
#include <setjmp.h>


/*
 * try to fix the race condition between the alarm call and the pause
 * call.
 *
 */


static unsigned sleep2(unsigned nsecs);
static void on_sig_alrm(int signo);
static void race(long);

static long     N  =  0;
static jmp_buf  env_alrm;

int
main(void)
{
  sleep2(1);
  sleep2(1);
  sleep2(1);

  return 0;
}

void
on_sig_alrm(int signo)
{
  if (SIGALRM == signo)
    {
      printf("# %s\n", _str_(SIGALRM));

      longjmp(env_alrm, 1);
    }
}

unsigned
sleep2(unsigned nsecs)
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

  if (0 == setjmp(env_alrm))
    {
      alarm(nsecs);

      /* race condition: between alarm and pause */
      race(N);

      pause();
    }

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
