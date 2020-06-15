#include <_memory_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void*
self_memcpy1(void *dst, const void *src, size_t n) {
  char *d = (char *)dst;
  char const *s = (char const *)src;
  while (n--) {
    *d++ = *s++;
  }
  return dst;
}

void*
self_memcpy2(void *dst, const void *src, size_t n) {
  long *d = (long *)dst;
  long const *s = (long const *)src;
  if (!(0xfffffffcL & (unsigned long)s)
      && !(0xfffffffcL & (unsigned long)d)) {
    while (n >= 4) {
      *d++ = *s++;
      n -= 4;
    }
  }

  char *d1 = (char *)d;
  char const *s1 = (char const *)s;
  while (n--) {
    *d1++ = *s1++;
  }

  return dst;
}

void 
test_self_memcpy1(void) {
  int ia[] = {1,2,3,4,};
  int *ia1 = malloc(sizeof(ia));
  self_memcpy1(&ia1[0], &ia[0], sizeof(ia));
  free(ia1);
}

void
test_self_memcpy2(void) {
  int ia[] = {1,2,3,4,5,6,7,8,};
  int *ia1 = malloc(sizeof(ia));
  self_memcpy2(&ia1[0], &ia[0], sizeof(ia));
  free(ia1);
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

  test_self_memcpy1();
  test_self_memcpy2();
  return 0;
}
