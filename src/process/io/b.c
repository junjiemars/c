#include "_process_.h"
#include <stdio.h>

int  g_var  =  1;
char ss[]   =  "#into stdout\n";

int
main()
{
  int    rc;
  int    stat;
  int    a_var  =  1;
  pid_t  pid;

  rc = write(STDOUT_FILENO, ss, sizeof(ss)-1);
  if (rc == -1)
    {
      perror("!panic:");
      exit(1);
    }

  printf("#before fork\n");

  pid = fork();
  if (pid == -1)
    {
      perror("!panic:");
      exit(1);
    }
  else if (pid == 0)
    {
      g_var++;
      a_var++;
    }
  else
    {
      pid = waitpid(pid, &stat, 0);
      if (pid == -1)
        {
          perror("!panic:");
          exit(1);
        }
    }

  printf("pid=%08ld, g_var=%d, a_var=%d\n", (long) getpid(), g_var, a_var);

  return 0;
}
