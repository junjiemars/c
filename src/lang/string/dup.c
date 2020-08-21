#include <_lang_.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#if MSVC
/* warning C4996: 'strdup': The POSIX name for this item is
	 deprecated. Instead, use the ISO C and C++ conformant name:
	 _strdup */
#  pragma warning(disable : 4996)
#endif


typedef char *(*strdup_fn)(const char *s);
typedef char *(*strndup_fn)(const char *s, size_t n);

char *self_strdup(const char *s);
char *self_strndup(const char *s, size_t n);

static void test_strdup(strdup_fn fn, const char *s);
static void test_strndup(strndup_fn fn, const char *s, size_t n);

char *
self_strdup(const char *s) {
  char *s1;
  s1 = malloc(strlen(s) + 1);
  if (s1) {
    strcpy(s1, s);
    return s1;
  }
  return 0;
}

char *
self_strndup(const char *s, size_t n) {
  char *s1;
  s1 = malloc(n+1);
  if (s1) {
    strncpy(s1, s, n);
    s1[n] = 0;
    return s1;
  }
  return 0;
}

void
test_strdup(strdup_fn fn, const char *s) {
  char *s1;
  s1 = fn(s);
  if (!s1) {
    perror(0);
    return;
  }
  printf("dup: %s\n", s1);
  free(s1);
}

void
test_strndup(strndup_fn fn, const char *s, size_t n) {
  char *s1;
  s1 = fn(s, n);
  if (!s1) {
    perror(0);
    return;
  }
  printf("ndup: %s\n", s1);
  free(s1);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  if (argc < 2) {
    printf("what the source string to dup\n");
    return 0;
  }
  
  const char *s = argv[1];
  test_strdup(strdup, s);
  test_strndup(strndup, s, 5);

  test_strdup(self_strdup, s);
  test_strndup(self_strndup, s, 5);

	return 0;
}
