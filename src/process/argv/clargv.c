#include <stdio.h>
#include <assert.h>

/*
 * It's guaranteed by both ISO C and POSIX.1
 * that `argv[argc] == NULL' is true
 *
 */

int
main(int argc, char **argv)
{
  int  i  =  0;

  while (*argv)
    {
      printf("%-16p->%16p: argv[%d]: %s\n", argv, &argv, i++, *argv);
      argv++;
    }

  assert(i == argc);

  return 0;
}
