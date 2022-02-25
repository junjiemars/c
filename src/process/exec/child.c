#include "_process_.h"
#include <stdio.h>

int
main(void)
{
  int    rc          =  0;
  int    stat;
  pid_t  pid;
  char *const env[]  =  { "XXX=xxx", 0 };

  pid = fork();
  if (pid == -1)
    {
      perror("!panic:");
      exit(1);
    }
  else if (pid == 0)
    {
      rc = execle(_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *) 0, env);
      if (rc == -1)
        {
          perror("!panic:");
          exit(1);
        }
      exit(0);
    }

  pid = waitpid(pid, &stat, 0);
  if (pid == -1)
    {
      perror("!panic:");
      exit(1);
    }

  pid = fork();
  if (pid == -1)
    {
      perror("!panic:");
      exit(1);
    }
  else if (pid == 0)
    {
      rc = execlp(_FILE_NAME_, "a", "b", "c", (char *) 0);
      if (rc == -1)
        {
          perror("!panic:");
          exit(1);
        }
      exit(0);
    }

#if (_WAIT_)
  pid = waitpid(pid, &stat, 0);

#endif

  return 0;
}
