#include "ndef.h"
#include "nstr.h"
#include <stdio.h>
#include <stdlib.h>

static void test_strdup(char*);

void
test_strdup(char *s)
{
  char  *ss  =  0;
  ss = strdup(s);
  free(ss);
}


int
main(_unused_(int argc), char **argv)
{
  test_strdup(argv[0]);

  return 0;
}
