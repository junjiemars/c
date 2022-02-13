#include <stdio.h>
#include <stdlib.h>

/*
 * 1. `environ' locate at the space between the top of the address space of the
 *    process and the top of stack. The space also include command line
 *    arguments and cannot be expanded upward or downward.
 * 2. `putenv', `setenv', or `unsetenv' causes `environ' be realloced.
 *
 */

extern char **environ;

static void print_environ(void);

static void
print_environ(void)
{
  char        **ss  =  0;
  static int    sn  =  0;

  ss = environ;
  printf("%2d. environ at %p\n------------\n", sn++, ss);

  while (*ss)
    {
      printf("%8p: %s\n", *ss, *ss);
      ss++;
    }

  printf("------------\n");
}


int
main(void)
{
  /* before change */
  print_environ();

  putenv("X1=x");
  setenv("X2", "xx", 0);

  /* after change */
  print_environ();

  /* after remove */
  unsetenv("X1");
  print_environ();

  return 0;
}
