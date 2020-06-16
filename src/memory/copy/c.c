#include <_memory_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#if CLANG
#  define typeof __typeof
#elif MSVC
#  define typeof decltype
#endif
#define _align_(x, a)           _align_mask_(x, (uintptr_t)(a)-1)
#define _align_mask_(x, mask)   (((uintptr_t)(x)+(mask)) & ~(mask))

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
  int *d = (int *)dst;
  int const *s = (int const *)src;

#ifdef _align_
  if ((int*)_align_(d, sizeof(int)) == d
      && (int*)_align_(s, sizeof(int)) == s) {
    while (n >= 4) {
      *d++ = *s++;
      n -= 4;
    }
  }
#endif
  char *d1 = (char *)d;
  char const *s1 = (char const *)s;
  while (n--) {
    *d1++ = *s1++;
  }

  return dst;
}


void 
test_self_memcpy1(const int *rs, size_t n) {
  int *ia1 = malloc(sizeof(int)*n);
  self_memcpy1(ia1, rs, sizeof(int)*n);
  free(ia1);
}

void
test_self_memcpy2(const int *rs, size_t n) {
  int *raw_ptr = 0;
  int *ptr = 0;
#ifdef _align_
  raw_ptr = malloc(sizeof(int)*(n+sizeof(int)-1));
  ptr = (int*)_align_(raw_ptr, sizeof(int));
#else
  raw_ptr = malloc(sizeof(int)*n);
  ptr = raw_ptr;
#endif
  self_memcpy2(ptr, rs, sizeof(int)*n);
  free(raw_ptr);
}

int
ranged_randomize(int min, int max) {
	int r = rand() / (RAND_MAX + 1.0) * (max - min) + min;
	return r;
}

int 
main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "random size ?\n");
    return 0;
  }
  _unused_(argv);
  int n = atoi(argv[1]);
  srand(time(0));

  int *raw_rs = 0;
  int *rs = 0;
#ifdef _align_
  raw_rs = malloc(sizeof(int)*(n+sizeof(int)-1));
  rs = (int*)_align_(raw_rs, sizeof(int));
#else
  raw_rs = malloc(sizeof(int)*n);
  rs= raw_rs;
#endif
  if (0 == raw_rs) {
    perror(0);
    return 1;
  }

  int *p = rs;
  for (int i = 0; i < n; i++) {
    p[i] = ranged_randomize(0, 100);
  }

  /* test_self_memcpy1(rs, n); */
  test_self_memcpy2(rs, n);
  
  free(raw_rs);
  return 0;
}
