#include "_lang_.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

size_t
str_len(const char *s) {
  size_t len = 0;
  while (*s++) {
    len++;
  }

  return len;
}

int
str_cmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
    s1++, s2++;
  }
  /* On some systems char is signed (more common). On others, char is unsigned. Defining the "sign-ness" of the last comparison promotes portability. Note that fgetc() obtains characters as unsigned char */
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *
str_cpy(char *dst, const char *src) {
  char *r = dst;
  while (0 != (*dst++ = *src++));

  return r;
}


int
main(int argc, char **argv) {
  _unused_(argc);

  size_t len1 = strlen(argv[0]);
  size_t len2 = str_len(argv[0]);
  assert((len1 == len2) || "str_len() fn failed");

  char *dst1 = malloc(len1+1);
  char *r1 = strcpy(dst1, argv[0]);
  assert((0 == strcmp(r1, argv[0])) && (r1 == dst1) || "strcpy() failed");
  free(dst1);

  char *dst2 = malloc(len2+1);
  char *r2 = str_cpy(dst2, argv[0]);
  assert((0 == str_cmp(r2, argv[0])) && (r2 == dst2) || "str_cpy() failed");
  free(dst2);
                    
}
