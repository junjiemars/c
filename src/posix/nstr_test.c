#include "ndef.h"
#include "nstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>


#if (MSVC)
#  pragma warning(disable: 4996)
#endif


static void test_strdup(void);
static void test_strerror_r(void);


int
main(void)
{
  test_strdup();
  test_strerror_r();

  return 0;
}


void
test_strdup(void)
{
#if !(NM_HAVE_STRDUP)
  printf();

#else
  char  *s1  =  "abc";
  char  *s2;
  s2 = strdup(s1);
  assert(strcmp(s1, s2) == 0);

  free(s2);
#endif  /* strdup */

}


void
test_strerror_r(void)
{
#if !(NM_HAVE_STRERROR_R)
  printf("%s: no `strerror_r' found\n", __FUNCTION__);

#else
  char buf[BUFSIZ] = {0};
  if (strerror_r(EPERM, buf, BUFSIZ))
    {
      perror(NULL);
    }
  else
    {
      printf("%s = %s\n", _str_(EPERM), buf);
    }

#endif
}
