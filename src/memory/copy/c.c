#include <_memory_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ints.h>


#define _align_(x, a)           _align_mask_(x, (uintptr_t)(a)-1)
#define _align_mask_(x, mask)   (((uintptr_t)(x)+(mask)) & ~(mask))


#if !(NM_HAVE_RESTRICT_KEYWORD)
#  if (NM_HAVE___RESTRICT_KEYWORD)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif


#define _time_(E, V) do {                       \
    clock_t _epoch_1_ = clock();                \
    (E);                                        \
    V = (clock() - _epoch_1_);                  \
  } while (0)

long
ranged_randomize(long min, long max) {
	long r = rand() / (RAND_MAX + 1.0) * (max - min) + min;
	return r;
}


void*
self_memcpy1(void *restrict dst, const void *restrict src, size_t n) {
  char *d = (char *)dst;
  char const *s = (char const *)src;
  while (n--) {
    *d++ = *s++;
  }
  return dst;
}

void*
self_memcpy2(void *restrict dst, const void *restrict src, size_t n) {
  long *d = (long *)dst;
  long const *s = (long const *)src;

#ifdef _align_
  if ((long*)_align_(d, sizeof(long)) == d
      && (long*)_align_(s, sizeof(long)) == s) {
    while (n >= sizeof(long)) {
      *d++ = *s++;
      n -= sizeof(long);
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
test_native_memcpy(long *dst, const long *src, long n, long x) {
  clock_t elapsed;
  double sum = 0.0;

  for (long i = 0; i < x; i++) {
    _time_(memcpy(dst, src, sizeof(long)*n), elapsed);
    sum += elapsed;
  }

  printf("%16s[%li,...,%li] elpased %8li cpu time, %16lf ms\n",
         "native_memcpy",
         dst[0], dst[n-1],
         (long)sum/x, (double)(sum*1000.0/(x*CLOCKS_PER_SEC)));
}

void 
test_self_memcpy1(long *dst, const long *src, long n, long x) {
  clock_t elapsed;
  double sum = 0.0;

  for (long i = 0; i < x; i++) {
    _time_(self_memcpy1(dst, src, sizeof(long)*n), elapsed);
    sum += elapsed;
  }

  printf("%16s[%li,...,%li] elpased %8li cpu time, %16lf ms\n",
         "self_memcpy1",
         dst[0], dst[n-1],
         (long)sum/x, (double)(sum*1000.0/(x*CLOCKS_PER_SEC)));
}

void
test_self_memcpy2(long *dst, const long *src, long n, long x) {
  clock_t elapsed;
  double sum = 0.0;

  for (long i = 0; i < x; i++) {
    _time_(self_memcpy2(dst, src, n), elapsed);
    sum += elapsed;
  }

  printf("%16s[%li,...,%li] elpased %8li cpu time, %16lf ms\n",
         "self_memcpy2",
         dst[0], dst[n-1],
         (long)sum/x, (double)(sum*1000.0/(x*CLOCKS_PER_SEC)));
}


int 
main(int argc, const char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "random size ?\n");
    return 0;
  }
  long n = atol(argv[1]);
  long x = atol(argv[2]);

  long *raw_src = 0, *raw_dst = 0;
  long *src = 0, *dst = 0;
  
#ifdef _align_
  raw_src = malloc(sizeof(long)*(n+sizeof(long)-1));
  raw_dst = malloc(sizeof(long)*(n+sizeof(long)-1));
  src = (long*)_align_(raw_src, sizeof(long));
  dst = (long*)_align_(raw_dst, sizeof(long));
#else
  raw_src = malloc(sizeof(long)*n);
  raw_dst = malloc(sizeof(long)*n);
  src = raw_src;
  dst = raw_dst;
#endif
  if (!raw_src) {
    perror(0);
    return 0;
  }

  for (long i = 0; i < n; i++) {
    src[i] = ranged_randomize(1, 100);
  }

  test_native_memcpy(dst, src, n, x);
  test_self_memcpy1(dst, src, n, x);
  test_self_memcpy2(dst, src, n, x);

  free(raw_dst);
  free(raw_src);
  return 0;
}
