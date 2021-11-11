#include "kws.h"

#if !defined(_unused_)
#define _unused_(x)  ((void)(x))
#endif

static void test_restrict(const char *restrict);


void
test_restrict(const char *restrict ss)
{
  _unused_(ss);
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  test_restrict((const char *restrict) argv[0]);
}
