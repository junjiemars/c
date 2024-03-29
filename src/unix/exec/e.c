#include "_unix_.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#if (LINUX) || (DARWIN)
#  include <unistd.h>
#  define _execve_t int
#elif (WINNT)
#  include <process.h>
#  define execve _execve
#  define _execve_t intptr_t
#endif

/* extern char **environ; */

int
main(int argc, char **argv, char **envp)
{
  if (argc < 2)
    {
      fprintf(stderr, "please, input at least one argument.\n");
      return -1;
    }

  /* char **p = envp; */
  /* while (*p) { */
  /*   printf("%s\n", *p++); */
  /* } */

  _execve_t has_err;
  has_err = execve(argv[1], &argv[1], envp);
  if (has_err)
    {
      perror(0);
    }
  return (int)has_err;
}
