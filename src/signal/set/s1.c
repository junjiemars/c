#include "_signal_.h"
#include <stdio.h>
#include <stdlib.h>


int
main(void)
{
  sigset_t  oset;

  sigprocmask(0, NULL, &oset);

  if (sigismember(&oset, SIGQUIT))
    {
      printf("SIGQUIT\n");
    }

  if (sigismember(&oset, SIGTERM))
    {
      printf("SIGTERM\n");
    }

  if (sigismember(&oset, SIGUSR1))
    {
      printf("SIGUSR1\n");
    }

  return 0;
}
