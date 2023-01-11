#include "_signal_.h"


/*
 * 1. emulate sleep.
 * 2. there is race condition.
 * 3. alarm and pause had been obsolete.
 *
 */

extern unsigned int  sleep(unsigned);


static void  test_sleep(unsigned int);
static void  on_sig_alrm(int signo);


unsigned int  N  =  1;


int
main(int argc, char **argv)
{
  if (argc > 1)
    {
      N = (unsigned int) atol(argv[1]);
    }
  printf("%d\n", getpid());

  test_sleep(N);

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

void
test_sleep(unsigned nsecs)
{
  unsigned  rc;
  double    elapsed;

  if (SIG_ERR == signal(SIGALRM, on_sig_alrm))
    {
      perror(NULL);
      return;
    }

  _time_(rc = sleep(nsecs), elapsed);

  printf("sleep(%d) return %d, elapsed %04f\n", nsecs, rc, elapsed);

}
