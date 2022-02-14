#include "ndef.h"
#include "nasrt.h"
#include <stdio.h>

static void test_assert(int, int);
static void test_static_assert(void);


void
test_assert(int a, int b)
{
  _unused_(a);
  _unused_(b);

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
main(int argc, char **argv)
{
  _unused_(argv);

  test_assert(argc, argc);
  test_static_assert();

  return 0;
}
