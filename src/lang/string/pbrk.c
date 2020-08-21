#include <_lang_.h>
#include <string.h>
#include <stdio.h>

typedef char *(*strpbrk_fn)(const char *ss, const char *d);

static void test_strpbrk(strpbrk_fn, const char *ss, const char *d);

void
test_strpbrk(strpbrk_fn fn, const char *ss, const char *d) {
  char *s1 = fn(ss, d);
  if (s1) {
    fprintf(stdout, "|%s|\n", s1);
  } else {
    fprintf(stdout, "%s: no found\n", d);
  }
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  if (argc < 3) {
    printf("where the source string and delim?\n");
    return 0;
  }

  const char *ss = argv[1];
  const char *d = argv[2];
  test_strpbrk(strpbrk, ss, d);
  
  return 0;
}
