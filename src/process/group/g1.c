#include "_process_.h"

int
main(void)
{
  pid_t  pid, pgid, ppid;

  pid = getpid();
  pgid = getpgid(pid);
  ppid = getppid();

  assert(pgid == getpgid(0) && pgid == getpgrp());

  printf("pid=%d, pgid=%d, ppid=%d\n", pid, pgid, ppid);

  if (pid != pgid)
    {
      if (setpgid(0, pid) == -1)
        {
          perror(NULL);
          exit(1);
        }
      pgid = getpgid(pid);
      printf("setpgid(%d, %d) -> pid=%d, pgid=%d, ppid=%d\n",
             0, pid, pid, pgid, ppid);
    }

  if (setpgid(0, 0) == -1)
    {
      perror(NULL);
      exit(1);
    }
  pgid = getpgid(pid);
  printf("setpgid(%d, %d) -> pid=%d, pgid=%d, ppid=%d\n",
         0, 0, pid, pgid, ppid);

  if (setpgid(0, ppid) == -1)
    {
      perror(NULL);
      exit(1);
    }
  pgid = getpgid(pid);
  printf("setgpid(%d, %d) -> pid=%d, pgid=%d, ppid=%d\n",
         0, ppid, pid, pgid, ppid);

  exit(0);
}
