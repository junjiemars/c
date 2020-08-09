#include "cffix.h"
#include <stdio.h>
#include <errno.h>

#if (MSVC)
#  pragma warning(disable: 4996)
#endif


int
main(int argc, char **argv) {
  if (argc < 2) {
    printf("input: <number>, '<string>'\n");
    return 0;
  }

  int d;
  char s[16] = { 0 };
  int n = sscanf(argv[1], "%d, %s", &d, s);
  if (EOF == n) {
    perror("!panic");
    return errno;
  }
  
  int i = inc(d);
  size_t len = str_len(s);
  printf("inc(%i) = %i, str_len(%s) = %zu\n", d, i, s, len);

  return 0;
}
