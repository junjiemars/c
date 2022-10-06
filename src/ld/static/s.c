#include <_ld_.h>

int
main(void)
{
  int  rc;

  rc = write(STDOUT_FILENO, "abc", sizeof("abc")-1);

  return rc;
}
