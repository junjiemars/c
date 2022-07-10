#include "ndef.h"
#include "nasrt.h"
#include <stdio.h>

static void test_assert(int, int);
static void test_static_assert(void);


void
test_assert(_unused_(int a), _unused_(int b))
{
  assert(a == b);
  printf("%s\n------------\n", __FUNCTION__);
}

void
test_static_assert(void)
{
  static_assert(sizeof(char) == 1, "sizeof(char) is not 1 byte");
  printf("%s\n------------\n", __FUNCTION__);
}


int
main(int argc, _unused_(char **argv))
{
  test_assert(argc, argc);
  test_static_assert();

  return 0;
}
