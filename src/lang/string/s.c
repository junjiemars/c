#include "../_lang_.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#if !defined(NM_HAVE_STR_ANY_S_FN)
#include <stdio.h>
#else

void
test_str_any_s (void)
{
  const char *xxx = "xxxxxxxx";
  size_t len = strlen (xxx);
  char *x = malloc (sizeof (char) * (len + 1));

  errno_t e = strcpy_s (x, sizeof (char) * (len + 1), xxx);
  assert ((0 == e) && (0 == strcmp (x, xxx)) && "strcpy_s() failed");
  free (x);
}

#endif /* end of NM_HAVE_STR_ANY_S_FN */

int
main (void)
{

#if !defined(NM_HAVE_STR_ANY_S_FN)
  printf ("skip str*_s fn testing\n");
#else
  test_str_any_s ();
#endif
}
