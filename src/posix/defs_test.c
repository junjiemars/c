#include "defs.h"
#include <inttypes.h>
#include <stdio.h>


#if !defined(_unused_)
#define _unused_(x)  ((void)(x))
#endif

static void test_restrict(const char *restrict);
static void test_assert(int, int);
static void test_static_assert(void);


void
test_restrict(const char *restrict ss)
{
  _unused_(ss);
  printf("%s\n------------\n", __FUNCTION__);
}


void
test_assert(int a, int b)
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
main(int argc, char **argv)
{
  test_restrict((const char *restrict) argv[0]);
  test_assert(argc, argc);
  test_static_assert();

  return 0;
}
