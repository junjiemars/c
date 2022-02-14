#include "_process_.h"
#include <stdio.h>
#include <stdlib.h>


int
main(void)
{
  int     stat;
  char   *x1  =  "x";
  char   *x2  =  "xx";
  pid_t   pid;

  setenv("X1", x1, 0);

  pid = fork();
  if (0 == pid)
    {
      printf("child: X1 = %s\n", getenv("X1"));
      setenv("X2", x2, 0);
      exit(0);
    }
  else
    {
      waitpid(pid, &stat, 0);
      printf("parent: X2 = %s\n", getenv("X2"));
    }
}
