#include "_process_.h"

/*
 * 1. On Linux, a child that terminates but had not been waited for
 * becomes a zombie.
 *
 * 2. On Darwin,
 *
 */



static char  cmd[NM_LINE_MAX];


int
main(void)
{
  int    stat;
  pid_t  pid;

  printf("parent[%d]\n", getpid());

  for (int i = 0; i < 5; i++)
    {
      pid = fork();
      if (1 == -pid)
        {
          perror(0);
          exit(errno);
        }

      if (0 == pid)
        {
          printf("child[%d]\n", getpid());
          exit(EXIT_SUCCESS);
        }

      /* only wait odd ones, the even ones should be zombies */
      if (1 == (i & 1))
        {
          waitpid(pid, &stat, 0);
          printf("child[%d] exit(%d)\n", pid, stat);
        }
      else
        {
          snprintf(cmd, NM_LINE_MAX, "ps -l -p %d", pid);
          system(cmd);
        }
    }

  exit(EXIT_SUCCESS);
}
