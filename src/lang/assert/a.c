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
    assert(((0 < x) && (x < 100)) && "x !in (0, 100)");
    return (x * x);
}

int
main(int argc, const char **argv)
{
    int  n;

    if (argc < 2)
      {
        fprintf(stderr, "usage: one <int>\n");
        return 1;
      }

    printf("# %s mode\n",
#if (NDEBUG)
           "RELEASE"
#else
           "DEBUG"
#endif  /* NDEBUG */
        );

    static_assert(4 == sizeof(int), "sizeof(int) != 4 bytes");

    n = atoi(argv[1]);
    printf("sqr(%i)=%u\n", n, sqr(n));

    return 0;
}
