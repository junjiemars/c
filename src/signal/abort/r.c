#include "_signal_.h"

/*
 * 1. `abort(3)' never return to its caller.
 *
 * 2. output streams are flushed and closed is implementation defined.
 *
 */


static void  on_sig_abrt(int);


int
main(void)
{
  printf("%d\n", getpid());

  signal(SIGABRT, on_sig_abrt);

  abort();

  printf("! never go here\n");

  exit(EXIT_SUCCESS);
}

void
on_sig_abrt(int signo)
{
  if (SIGABRT == signo)
    {
      printf("# %s\n", _str_(SIGABRT));

      /* cleanup then exit*/
    }
}
