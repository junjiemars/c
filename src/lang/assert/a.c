#include <_lang_.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#if !(NM_HAVE_STATIC_ASSERT)
#  ifdef static_assert
#    undef static_assert
#  endif
#  define static_assert(e, m) enum {static_assert = 1/!!((e) && (m))}
#endif

int
sqr(int x)
{
	assert(((0 < x) && (x < 100)) && "0 < x < 100");
	return (x * x);
}

int
main(int argc, const char* argv[])
{
	assert((argc > 1) && "usage: one <int>");

  char *mode =
#if (NDEBUG)
    "RELEASE";
#else
  "DEBUG";
#endif
	printf("in %s mode\n", mode);

	static_assert(4 == sizeof(int), "sizeof(int) != 4 bytes");

	if (argc > 1)
    {
      int n = atoi(argv[1]);
      printf("sqr(%i)=%u\n", n, sqr(n));
    }

	return 0;
}
