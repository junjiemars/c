#include "nustd.h"
#include <stdio.h>

static void test_sleep(void);
static void test_getpid(void);

void
test_sleep(void)
{
  sleep(1);
}

void
test_getpid(void)
{
  getpid();
}


int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

#if (LINUX)
#ifdef _GNU_SOURCE
  printf("_GNU_SOURCE\n");
#endif

#ifdef _POSIX_C_SOURCE
  printf("_POSIX_C_SOURCE: %ldL\n", (long) _POSIX_C_SOURCE);
#endif

#endif  /* LINUX */



  test_sleep();
  test_getpid();

  return 0;
}
