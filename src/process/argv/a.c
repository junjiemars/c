#include <stdio.h>
#include <assert.h>

/*
 * 1. It's guaranteed by both ISO C and POSIX.1
 * that `argv[argc] == NULL' is true
 *
 * 2. There is an implicit argument: `envp' and
 * `envp == environp' is true.
 *
 */

extern char  **environ;

int
main(int argc, char *argv[], char *envp[])
{
  int  i;

  i = 0;
  while (*argv)
    {
      printf("%-16p->%16p: argv[%d]: %s\n", argv, *argv, i++, *argv);
      argv++;
    }
  assert(i == argc);

  assert(&environ[0] == &envp[0]);

  i = 0;
  while (*envp)
    {
      printf("%-16p->%16p: envp[%d]: %s\n", envp, *envp, i++, *envp);
      envp++;
    }

  return 0;
}
