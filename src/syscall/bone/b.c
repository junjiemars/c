#include "_syscall_.h"


static void  on_sigusr1(int);


int
main(void)
{
  pid_t  tid;

  signal(SIGUSR1, on_sigusr1);

  tid = syscall(SYS_gettid);

  syscall(SYS_tgkill, getpid(), tid, SIGUSR1);
}

void
on_sigusr1(int signo)
{
  if (signo == SIGUSR1)
    {
      printf("# received %s(%d)\n", _str_(SIGUSR1), signo);
    }
}
