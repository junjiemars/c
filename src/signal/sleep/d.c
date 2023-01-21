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

  if (argc > 1)
    {
      N = (unsigned int) atol(argv[1]);
    }

  setvbuf(stdout, NULL, _IONBF, 0);
  printf("%d, %u\n", getpid(), N);

  signal(SIGALRM, on_sig_alrm);

  n = sleep(0);
  printf("%u = sleep(%u)\n", n, 0);

  n = sleep(N);
  printf("%u = sleep(%u)\n", n, N);

  alarm(N+N/2);
  n = sleep(N);
  printf("alarm(%u), %u = sleep(%u)\n", N+N/2, n, N);

  alarm(N/2);
  n = sleep(N);
  printf("alarm(%u), %u = sleep(%u)\n", N/2, n, N);

  return 0;
}


void
on_sig_alrm(int signo)
{
  printf("# %s(%d)\n", _str_(SIGALRM), signo);
}
