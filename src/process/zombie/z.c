#include "_process_.h"
#include <stdio.h>
#include <sys/wait.h>


int
main(void)
{
  int    i;
  int    stat;
  pid_t  pid;
  char   cmd[256];

  printf("parent[%d]\n", getpid());

  for (i = 0; i < 10; i++)
    {
      pid = fork();
      if (0 == pid)
        {
          printf("child[%d]\n", getpid());
          exit(0);
        }

      sleep(2);

      if (0 == (i & 2))
        {
          waitpid(pid, &stat, 0);
          printf("child[%d] exit(%d)\n", pid, stat);
        }
      else
        {
          sprintf(cmd, "ps aux|grep %d", pid);
          system(cmd);
        }
    }
}
