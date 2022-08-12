#include "ndef.h"
#include "nstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#if (MSVC)
#  pragma warning(disable:4996)
#endif


static void test_strdup(char*);


int
main(__attribute__((unused)) int argc, char **argv)
{
  test_strdup(argv[0]);

  return 0;
}


void
test_strdup(char *s)
{
  char  *ss  =  NULL;

  ss = strdup(s);
  assert(strcmp(s, ss) == 0);

  free(ss);
}
