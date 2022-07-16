#include <_signal_.h>

/*
 * 1. raise function was defined by ISO C.
 *
 * 2. kill is a system call.
 *
 */


static void on_sig_usr(int);


int
main()
{
  signal(SIGUSR1, on_sig_usr);
  signal(SIGUSR2, on_sig_usr);

  raise(SIGUSR1);
  kill(getpid(), SIGUSR2);

  exit(EXIT_SUCCESS);
}

void
on_sig_usr(int signo)
{
  if (SIGUSR1 == signo)
    {
      printf("# %s\n", _str_(SIGUSR1));
    }
  else if (SIGUSR2 == signo)
    {
      printf("# %s\n", _str_(SIGUSR2));
    }
}
