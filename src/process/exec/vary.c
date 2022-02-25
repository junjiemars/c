#include "_process_.h"
#include <stdio.h>

int
main(int argc, char * argv[])
{
  int  rc              =  0;
  char *env[]          =  { "XXX=xxx", 0 };
  char *const  varg[]  =  { _FILE_NAME_, "a", "b", "c", 0};

  if (argc < 2)
    {
      printf("!panic: argv[1] == exec...\n");
      return 0;
    }
  printf("%s------------\n", argv[1]);

  if (0 == strcmp("execl", argv[1]))
    {
      /* arguments as List */
      rc = execl(_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *) 0);

    }
  else if (0 == strcmp("execlp", argv[1]))
    {
      /* arguments as List and using PATH environment variable */
      rc = execlp(_FILE_NAME_, _FILE_NAME_, "a", "b", "c", (char *) 0);

    }
  else if (0 == strcmp("execle", argv[1]))
    {
      /* arguments as List and passing Environment vector */
      rc = execle(_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *) 0, env);

    }
  else if (0 == strcmp("execv", argv[1]))
    {
      /* arguments as Vector */
      rc = execv(_PATH_NAME_, varg);

    }
  else if (0 == strcmp("execvp", argv[1]))
    {
      /* arguments as Vector and using PATH environment variable */
      rc = execvp(_FILE_NAME_, varg);

    }

  else
    {
      printf("!panic: unknown exec fn\n");
    }

  if (rc == -1)
    {
      perror("!panic:");
    }

  return 0;
}
