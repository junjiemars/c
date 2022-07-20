#include <_lang_.h>

/*
 * configure --has-lang --with-optimize=-O1
 *
 */



#if !(NM_HAVE_RESTRICT)
#  if (NM_HAVE___RESTRICT)
#    define restrict __restrict
#  endif
#endif  /* NM_HAVE_RESTRICT */


static void f1(int*, int*, int*);
static void f2(int*, int*, int*restrict);

int
main(int argc, _unused_(char **argv))
{

  printf("support restrict keyword = %s\n----------\n",
#if (NM_HAVE_RESTRICT) || (NM_HAVE___RESTRICT)
         "yes"
#else
         "no"
#endif
         );

  int x = argc;
  int y = argc * 10;
  int z = argc * 100;

  f1(&x, &y, &z);
  printf("x=%d, y=%d, z=%d\n", x, y, z);

  f2(&x, &y, &z);
  printf("x=%d, y=%d, z=%d\n", x, y, z);

  return 0;
}


void
f1(int *p1, int *p2, int *val)
{
  *p1 += *val;
  *p2 += *val;
}

void
f2(int *p1, int *p2, int *restrict val)
{
  *p1 += *val;
  *p2 += *val;
}
