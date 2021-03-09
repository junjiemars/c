#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

size_t self_strnlen(const char *src, size_t len);
char *self_strncpy(char *dst, const char *src, size_t len);

typedef size_t (*strnlen_fn)(const char *src, size_t maxlen);
typedef char *(*strncpy_fn)(char *dst, const char *src, size_t len);
typedef int (*strncmp_fn)(const char *s1, const char *s2, size_t n);

static void test_strnlen(strnlen_fn fn, const char *src);
static void test_strncpy(strncpy_fn fn, char *src);
static void test_strncmp(strncmp_fn fn, const char *s1, const char *s2);

static void fill_str(char *dst, char c, size_t n);

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
	while (n-- && (0 != (*p++ = *src++)))
    {
      /* do nothing */
    }
	return dst;
}

int
self_strncmp(const char *s1, const char *s2, size_t n)
{
	while (*s1 && *s2 && (*s1 == *s2) && n > 1)
    {
      s1++, s2++, n--;
    }
	int cmp = *(unsigned char *)s1 - *(unsigned char *)s2;
  return cmp % 2;
}

void
test_strnlen(strnlen_fn fn, const char *s)
{
  size_t n;
  size_t len;
  size_t rn;

  n = strlen(s);

  /* len = n */
  len = n;
  rn = fn(s, len);
  ASSERT(rn == len);
  printf("strnlen | len = %zu, n = %zu, rn = %zu: %s\n",
         len, n, rn, s);
  
  /* len < n */
  len = n - 1;
  rn = fn(s, len);
  ASSERT(rn == len);
  printf("strnlen | len = %zu, n = %zu, rn = %zu: %s\n",
         len, n, rn, s);  

  /* len < n */
  len = n + 1;
  rn = fn(s, len);
  ASSERT(rn < len);
  printf("strnlen | len = %zu, n = %zu, rn = %zu: %s\n",
         len, n, rn, s);  
}

void
test_strncpy(strncpy_fn fn, char *src)
{
  char *dst = 0;
  char *d = 0;
  size_t n, len;

  n = strlen(src);
  dst = malloc(n + 1);
  fill_str(dst, '_', n);

  /* len = n */
  len = n;
  d = fn(dst, src, n);
  ASSERT(d == dst);
  printf("strncpy | len = %zu, n = %zu: %s, %s\n",
         len, n, src, dst);

  /* len < n */
  len = n - 1;
  d = fn(dst, src, len);
  ASSERT(dst[len-1] != 0);
  dst[len] = 0;
  printf("strncpy | len = %zu, n = %zu: %s, %s\n",
         len, n, src, dst);
  
  /* len > n */
  len = n + 1;
  d = fn(dst, src, len);
  ASSERT(dst[n] == 0);
  printf("strncpy | len = %zu, n = %zu: %s, %s\n",
         len, n, src, dst);

  free(dst);
}

void
test_strncmp(strncmp_fn fn, const char *s1, const char *s2)
{
  int cmp;
  size_t n1, n2, n;
  size_t len;

  n1 = strlen(s1);
  n2 = strlen(s2);
  n = n1 < n2 ? n1 : n2;

  /* len = n */
  len = n;
  cmp = fn(s1, s2, len);
  ASSERT(cmp == 0);
  printf("strncmp | len = %zu, n = %zu, cmp = %02i: %s, %s\n",
         len, n, cmp, s1, s2);
  
  /* len < n */
  len = n - 1;
  cmp = fn(s1, s2, len);
  printf("strncmp | len = %zu, n = %zu, cmp = %02i: %s, %s\n",
         len, n, cmp, s1, s2);

  /* len > n */
  len = n + 1;
  cmp = fn(s1, s2, len);
  printf("strncmp | len = %zu, n = %zu, cmp = %02i: %s, %s\n",
         len, n, cmp, s1, s2);
}

void
fill_str(char *dst, char c, size_t n)
{
  for (size_t i = 0; i < n; i++)

    {
      dst[i] = c;
    }
  dst[n] = 0;
}


int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("where the lhs and rhs strings\n");
      return 0;
    }

  char *s1 = argv[1];
  char *s2 = argv[2];

  printf("----------\n");
  test_strnlen(strnlen, s1);
  printf("----------\n");
  test_strnlen(self_strnlen, s1);

  printf("----------\n");
	test_strncpy(strncpy, s1);
  printf("----------\n");
  test_strncpy(self_strncpy, s1);

  printf("----------\n");
  test_strncmp(strncmp, s1, s2);
  test_strncmp(self_strncmp, s1, s2);

  return 0;
}
