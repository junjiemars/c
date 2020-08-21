#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t self_strnlen(const char *src, size_t len);
char *self_strncpy(char *dst, const char *src, size_t len);

typedef size_t (*strnlen_fn)(const char *src, size_t maxlen);
typedef char *(*strncpy_fn)(char *dst, const char *src, size_t len);
typedef int (*strncmp_fn)(const char *s1, const char *s2, size_t n);

static void test_strnlen(strnlen_fn fn, const char *src, size_t maxlen);
static void test_strncpy(strncpy_fn fn, char *src, size_t len);
static void test_strncmp(strncmp_fn fn,
                         const char *s1, const char *s2, size_t n);

size_t
self_strnlen(const char *s, size_t maxlen) {
	size_t n = 0;
	while (*s++ && maxlen--) {
		n++;
	}
	return n;
}

char *
self_strncpy(char *dst, const char *src, size_t n) {
	char *p = dst;
	while (0 != (*p++ = *src++) && n--) {
    /* do nothing */
  }
	return dst;
}

int
self_strncmp(const char *s1, const char *s2, size_t n) {
	while (*s1 && (*s1 == *s2) && n > 1) {
		s1++, s2++, n--;
	}
  
	int cmp = *(const unsigned char*)s1 - *(const unsigned char*)s2;
  if (cmp < 0) {
    return -1;
  } else if (cmp > 0) {
    return 1;
  }
  return 0;
}

void
test_strnlen(strnlen_fn fn, const char *s, size_t maxlen) {
  size_t n;
  n = fn(s, maxlen);
  printf("[%zu]: %s\n", n, s);
}

void
test_strncpy(strncpy_fn fn, char *src, size_t n) {
  char *dst;
  dst = malloc(n + 1);
  (void)fn(dst, src, n);
  dst[n] = '\0';
  printf("%s\n", dst);
  free(dst);
}

void
test_strncmp(strncmp_fn fn, const char *s1, const char *s2, size_t n) {
  int cmp;
  cmp = fn(s1, s2, n);
  printf("==%i\n", cmp);
}


/* #endif /\* end of NM_HAVE_STRN_ANY_FN *\/ */

int
main(int argc, char **argv) {
  if (argc < 4) {
    printf("where the source string and length\n");
    return 0;
  }
  
  char *s1 = argv[1];
  char *s2 = argv[2];
  size_t n = atol(argv[3]);
  
  test_strnlen(strnlen, s1, n);
  test_strnlen(self_strnlen, s1, n);
  
	test_strncpy(strncpy, s1, n);
  test_strncpy(self_strncpy, s1, n);

  test_strncmp(strncmp, s1, s2, n);
  test_strncmp(self_strncmp, s1, s2, n);

  return 0;
}
