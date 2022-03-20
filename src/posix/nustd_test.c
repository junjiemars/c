#include "nustd.h"
#include <stdio.h>

static void test_sleep(void);
static void test_getpid(void);
static void test_conf(void);

int
main(void)
{
  test_conf();

  test_sleep();
  test_getpid();

  return 0;
}

void
test_conf(void)
{
#if (_POSIX_VERSION)
  printf("%s: %ld\n", _str_(_POSIX_VERSION), _POSIX_VERSION);
#endif

#if (_XOPEN_VERSION)
  printf("%s: %d\n", _str_(_XOPEN_VERSION), _XOPEN_VERSION);
#endif

#if (_POSIX_C_SOURCE)
  printf("%s: %ld\n", _str_(_POSIX_C_SOURCE), _POSIX_C_SOURCE);

#endif  /* _POSIX_C_SOURCE */

}

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
