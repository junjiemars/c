#include "_process_.h"

int
main(void)
{
  pid_t  sid, pid;

  if ((sid = setsid()) == -1)
    {
      perror(NULL);
      exit(1);
    }
  pid = getpid();

  printf("pid=%d, sid=%d\n", pid, sid);

  exit(0);
}
