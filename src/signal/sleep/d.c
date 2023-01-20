#include "_signal_.h"


/*
 * `sleep(3)'.
 *
 */

extern unsigned int  sleep(unsigned);


static void  on_sig_alrm(int signo);


unsigned int  N  =  1;


int
main(int argc, char **argv)
{
  unsigned int  n;
  double        elapsed;

  if (argc > 1)
    {
      N = (unsigned int) atol(argv[1]);
    }

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("%d\n", getpid());

  signal(SIGALRM, on_sig_alrm);

  _time_(n = sleep(0), elapsed);
  printf("%u = sleep(%02u), elapsed = %04f\n", n, 0, elapsed);

  _time_(n = sleep(N+10), elapsed);
  printf("%u = sleep(%02u), elapsed = %04f\n", n, N+10, elapsed);

  _time_(n = sleep(N), elapsed);
  printf("%u = sleep(%02u), elapsed = %04f\n", n, N, elapsed);

  return 0;
}


void
on_sig_alrm(int signo)
{
  printf("# %s(%d)\n", _str_(SIGALRM), signo);
}
