#include "ndef.h"
#include "nstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#if (MSVC)
#  pragma warning(disable: 4996)
#endif


static void test_strdup(void);


int
main(void)
{
  test_strdup();

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
