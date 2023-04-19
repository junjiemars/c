#include "_process_.h"

int
main(void)
{
  pid_t  sid, pid, pgid, ppid;

  pid = getpid();
  pgid = getpgid(0);
  ppid = getppid();
  sid = getsid(0);

  printf("sid=%d, pid=%d, pgid=%d, ppid=%d\n", sid, pid, pgid, ppid);

  if ((sid = setsid()) == -1)
    {
      perror(NULL);
      exit(1);
    }
  sid = getsid(0);
  pgid = getpgid(0);
  printf("setsid() -> sid=%d, pid=%d, pgid=%d, ppid=%d\n",
         sid, pid, pgid, ppid);

  exit(0);
}
