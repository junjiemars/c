#include <_memory_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
test_self_memcpy1(const int *rs, size_t n) {
  int *ia1 = malloc(sizeof(int)*n);
  self_memcpy1(ia1, rs, sizeof(int)*n);
  free(ia1);
}

void
test_self_memcpy2(const int *rs, size_t n) {
  int *ia1 = aligned_alloc(sizeof(int), sizeof(int)*n);
  self_memcpy2(ia1, rs, sizeof(int)*n);
  free(ia1);
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
  /* int n = atoi(argv[1]); */
  /* srand(time(0)); */

  /* int *rs = aligned_alloc(sizeof(int), sizeof(int)*n); */
  /* if (0 == rs) { */
  /*   perror(0); */
  /*   return 1; */
  /* } */

  /* test_self_memcpy1(rs, n); */
  /* test_self_memcpy2(rs, n); */
  
  /* free(rs); */
  return 0;
}
