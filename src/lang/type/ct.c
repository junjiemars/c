#include "_lang_.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#if (MSVC)
#  pragma warning(disable: 4244)
#endif

long
atox(const char *s) {
  static char const *x = "0123456789ABCDEF";
  long sum;
  while (isspace(*s++)) {
    /* do nothing */
  }
  for (sum = 0L; isxdigit(*s); ++s) {
    int d = strchr(x, toupper(*s)) - x;
    sum = sum * 16L + d;
  }
  return sum;
}

int
main(int argc, char **argv) {
  if (argc > 1) {
    long x = atox(argv[1]);
    printf("0x%s = 0d%ld\n", argv[1], x);
  }
  return 0;
}
