#include <_lang_.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#if MSVC
/* warning C4996: 'strcpy': This function or variable may be
	 unsafe. Consider using strcpy_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS. */
#  pragma warning(disable : 4996)
#endif

size_t
self_strlen(const char *s) {
  size_t len = 0;
  while (*s++) {
    len++;
  }

  return len;
}

int
self_strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++, s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *
self_strcpy(char *dst, const char *src) {
  char *r = dst;
  while (0 != (*dst++ = *src++));

  return r;
}


int
main(int argc, char **argv) {
  _unused_(argc);

  size_t len1 = strlen(argv[0]);
  size_t len2 = self_strlen(argv[0]);
  assert((len1 == len2) || "self_strlen() failed");

  char *dst1 = malloc(len1+1);
  char *r1 = strcpy(dst1, argv[0]);
  assert(((0 == strcmp(r1, argv[0]))
					&& (r1 == dst1)) || "strcpy() failed");
#if NDEBUG
	_unused_(r1);
#endif
  free(dst1);

  char *dst2 = malloc(len2+1);
  char *r2 = self_strcpy(dst2, argv[0]);
  assert(((0 == self_strcmp(r2, argv[0]))
					&& (r2 == dst2)) || "self_strcpy() failed");
#if NDEBUG
	_unused_(r2);
#endif
  free(dst2);
}
