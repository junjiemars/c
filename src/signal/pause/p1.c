#include "_signal_.h"


/*
 * Implementations derived from UNIX System V support the signal
 * function, but it provides the old unreliable signal semantics.
 *
 */

static void on_sig_usr1(int signo);
static void on_sig_term(int signo);


int
main(void)
{
  pid_t  pid;

  pid = getpid();
  signal(SIGUSR1, on_sig_usr1);
  signal(SIGTERM, on_sig_term);

  for (;;)
    {
      printf("# kill -USR1 %d\n# kill -TERM %d\n", pid, pid);
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

void
on_sig_term(int signo)
{
  if (SIGTERM == signo)
    {
      printf("! %s\n", _str_(SIGTERM));
      exit(EXIT_SUCCESS);
    }
}
