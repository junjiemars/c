#include "_lang_.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define N 8

#if (MSVC) && defined(_WIN64)
typedef __int64             ssize_t;
#else
typedef int                 ssize_t;
#endif


void test_null(int);
void test_array_boundary(char**);
void test_arr_tail(void);
void test_diff(int*);
void test_comp(int*);

void
test_null(int c)
{
  char *cp;
  cp = 0;
  cp = (char*) &c;
  
  ASSERT(cp);
}

void
test_array_boundary(char **a)
{
  _unused_(a);
}

void
test_arr_tail(void)
{
  int a[N];
  int *ap;

  for (ap = &a[0]; ap < &a[N]; )
    {
      *ap++ = 0;
    }
  ASSERT(ap == &a[N]);
}

void
test_diff(int *a)
{
  int *p0, *p1;
  ptrdiff_t one;
  ssize_t offset;
  
  p0 = &a[0];
  p1 = &a[1];

  one = p1 - p0;
  ASSERT(one == 1);

  offset = (ssize_t)p1 - (ssize_t)p0;
  ASSERT(offset == sizeof(int));

  one = p0 - p1;
  ASSERT(-one == 1);
  
  offset = (ssize_t)p0 - (ssize_t)p1;
  ASSERT(-offset == sizeof(int));
}

void
test_comp(int *a)
{
  int *p0, *p1;
  p0 = &a[0];
  p1 = &a[1];
  ASSERT(p0 < p1);
  ASSERT(p0 <= p1-1);
  ASSERT(p1 > p0);
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  int *a = malloc(N*sizeof(a[0]));
  if (!a)
    {
      perror(0);
      return errno;
    }
  for (int i = 0; i < N; i++)
    {
      a[i] = i;
    }
  
  test_null('a'); 
  test_array_boundary(argv);
  test_arr_tail();
  test_diff(a);
  test_comp(a);

  free(a);
  return 0;
}
