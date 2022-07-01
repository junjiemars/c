#include "_process_.h"
#include <stdio.h>

/*
 * 1. stdout is line buffered in terminal.
 * 2. stdout is fully buffered in file.
 *
 */


int  g_var  =  1;
char ss[]   =  "# into stdout\n";

int
main()
{
  int    rc;
  pid_t  pid;
  int    a_var  =  1;

  rc = write(STDOUT_FILENO, ss, sizeof(ss)-1);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("# before fork\n");

  pid = fork();
  if (pid == -1)
    {
      perror(NULL);
      exit(1);
    }
  else if (pid == 0)
    {
      g_var++;
      a_var++;
    }
  else
    {
      waitpid(pid, (int *) 0, 0);
    }

  printf("[pid:%08d]: g_var=%d, a_var=%d\n", getpid(), g_var, a_var);

  exit(EXIT_SUCCESS);
}
