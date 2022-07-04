#include "_signal_.h"
#include <stdio.h>
#include <stdlib.h>

static void on_sig_usr1(int signo);


int
main(void)
{
  printf("%d\n", getpid());

  if (SIG_ERR == signal(SIGUSR1, on_sig_usr1))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  for (;;)
    {
      printf("# pause\n");
      pause();
    }

  exit(EXIT_SUCCESS);
}


void
on_sig_usr1(int signo)
{
  if (SIGUSR1 == signo)
    {
      printf("! %s\n", _str_(SIGUSR1));
    }
}
