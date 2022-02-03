#include "_signal_.h"
#include <stdio.h>

static void on_sig_usr1(int signo);


static void
on_sig_usr1(int signo)
{
  if (signo == SIGUSR1)
    {
      printf("#received: SIGUSR1\n");
    }
  else
    {
      /* never reach here */
      printf("#received: %d\n", signo);
    }
}

int
main(void)
{
  printf("%d\n", getpid());

  if (SIG_ERR == signal(SIGUSR1, on_sig_usr1))
    {
      perror(NULL);
      return -1;
    }

  for (;;)
    {
      pause();
    }

  return 0;
}
