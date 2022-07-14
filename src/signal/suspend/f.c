#include <_signal_.h>


static void on_sig(int);


static volatile sig_atomic_t  qflag;


int
main(_unused_(int argc), _unused_(char **argv))
{
  sigset_t  nset, oset, zset;

  printf("%d\n", getpid());

  signal(SIGINT, on_sig);
  signal(SIGQUIT, on_sig);

  sigemptyset(&zset);
  sigemptyset(&nset);
  sigaddset(&nset, SIGQUIT);

  if (sigprocmask(SIG_BLOCK, &nset, &oset))
    {
      perror(NULL);
    };
  printf("! %s blocked\n", _str_(SIGQUIT));

  while (qflag == 0)
    {
      printf("! suspend enter...\n");
      sigsuspend(&zset);
    }
  qflag = 0;

  printf("! suspend return\n");

  if (sigprocmask(SIG_SETMASK, &oset, NULL))
    {
      perror(NULL);
    }
  printf("! %s unblocked\n", _str_(SIGQUIT));


  exit(EXIT_SUCCESS);
}

void
on_sig(int signo)
{
  if (SIGINT == signo)
    {
      printf("# %s, %d\n", _str_(SIGINT), qflag);
    }
  else if (SIGQUIT == signo)
    {
      qflag = 1;
      printf("# %s, %d\n", _str_(SIGQUIT), qflag);
    }
}
