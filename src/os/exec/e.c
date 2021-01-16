#include <_os_.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#if (LINUX) || (DARWIN)
#  include <unistd.h>
#elif (WINNT)
#  include <process.h>
#  define execve _execve
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
  
  int has_err = execve(argv[1], &argv[2], envp);
  if (has_err)
    {
      perror(0);
    }
  return has_err;
}
