#include "_signal_.h"
#include <setjmp.h>
#include <errno.h>

/*
 * extends `read(2)' to support `timeout'.
 *
 * 1. using `select(2)' instead `alarm(2)' and `siglongjmp(3)'.
 *
 */


ssize_t  read1(int, void*, size_t, int timeout);

ssize_t
read1(int fd, void *buf, size_t count, int timeout)
{
  /* !TODO: */
  return 0;
}
