#include "_syscall_.h"


static void  on_sigusr1(int);


int
main(void)
{
  pid_t  pid, tid;

  signal(SIGUSR1, on_sigusr1);

  pid = getpid();

  tid = syscall(SYS_gettid);

  assert(pid == tid);

  syscall(SYS_tgkill, pid, tid, SIGUSR1);
}

void
on_sigusr1(int signo)
{
  if (signo == SIGUSR1)
    {
      printf("# received %s(%d)\n", _str_(SIGUSR1), signo);
    }
}
