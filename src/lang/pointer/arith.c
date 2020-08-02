#include "_lang_.h"
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>

#define N 8

void test_null(int);
void test_array_boundary1(char**);
void test_arr_tail(void);
void test_diff(int*);
void test_comp(int*);

void
test_null(int c) {
  char *cp;
  cp = 0;
  cp = (char*) &c;
}

void
test_array_boundary1(char **a) {
  _unused_(a);
}

void
test_arr_tail(void) {
  int a[N];
  int *ap;

  for (ap = &a[0]; ap < &a[N]; ) {
    *ap++ = 0;
  }
  assert(ap == &a[N]);
}

void
test_diff(int *a) {
  int *p0, *p1;
  ptrdiff_t one;
  ssize_t offset;
  
  p0 = &a[0];
  p1 = &a[1];

  one = p1 - p0;
  assert(one == 1);

  offset = (ssize_t)p1 - (ssize_t)p0;
  assert(offset == sizeof(int));

  one = p0 - p1;
  assert(-one == 1);
  
  offset = (ssize_t)p0 - (ssize_t)p1;
  assert(-offset == sizeof(int));
}

void
test_comp(int *a) {
  int *p0, *p1;
  p0 = &a[0];
  p1 = &a[1];
  assert(p0 < p1);
  assert(p0 <= p1-1);
  assert(p1 > p0);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  int *a = malloc(N*sizeof(a[0]));
  if (!a) {
    perror(0);
    return errno;
  }
  for (int i = 0; i < N; i++) {
    a[i] = i;
  }
  
  test_null('a'); 
  test_array_boundary1(argv);
  test_arr_tail();
  test_diff(a);
  test_comp(a);

  free(a);
  return 0;
}
