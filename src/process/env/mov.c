#include "_process_.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 1. `environ' locate at the space between the top of the address
 *    space of the process and the top of stack. The space also
 *    include command line arguments and cannot be expanded upward or
 *    downward.
 * 2. `putenv', `setenv', or `unsetenv' causes `environ' be realloced.
 *
 */

extern char **environ;

static void print_environ(void);


int
main(void)
{
  /* before change */
  print_environ();

  setenv("X1", "x", 1);
  setenv("X2", "xx", 1);

  /* after change */
  print_environ();

  /* after remove */
  unsetenv("X1");
  print_environ();

  return 0;
}


void
print_environ(void)
{
  /* char         *x1, *x2; */
  char        **ss;
  static int    sn  =  0;

  ss = environ;
  printf("%2d. environ at %p\n------------\n", sn++, ss);

  /* x1 = getenv("X1"); */
  /* x2 = getenv("X2"); */

  /* printf("%-16p->%16p: %s\n", &x1, x1, x1); */
  /* printf("%-16p->%16p: %s\n", &x2, x1, x2); */

  while (*ss)
    {
      printf("%-16p->%16p: %s\n", ss, *ss, *ss);
      ss++;
    }


  printf("------------\n");
}
