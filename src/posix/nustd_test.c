#include "nustd.h"
#include <stdio.h>

static void test_sleep(void);
static void test_getpid(void);

void
test_sleep(void)
{
  printf("sleep(1) ...\n");
  sleep(1);
}

void
test_getpid(void)
{
  printf("pid: %d\n", getpid());
}


int
main(void)
{

#if (_POSIX_C_SOURCE)
  printf("_POSIX_C_SOURCE: %ldL\n", (long) _POSIX_C_SOURCE);

#endif  /* _POSIX_C_SOURCE */

  test_sleep();
  test_getpid();

  return 0;
}
