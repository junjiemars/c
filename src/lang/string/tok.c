#include <_lang_.h>
#include <string.h>
#include <stdio.h>
#include <posix/strs.h>

#if MSVC
/* warning C4996: 'strtok': This function or variable may be
   unsafe. Consider using strtok_s instead. To disable deprecation,
   use _CRT_SECURE_NO_WARNINGS */
#  pragma warning(disable : 4996)
#endif

static void test_strtok(char *, char *);
static void test_strtok_r(void);

void
test_strtok(char *ss, char *d) {
  char *tok = strtok(ss, d);
  while (tok) {
    printf("|%s|\n", tok);
    tok = strtok(0, d);
  }
}

void
test_strtok_r(void) {
  char outer[64], inner[64];
  char *d = "\\/:;=-";
  char *tok1, *lasts1, *tok2, *lasts2;
  
  strcpy(outer, "This;is.a:test:of=the/string\\tokenizer-function.");
  
  for (tok1 = strtok_r(outer, d, &lasts1);
       tok1;
       tok1 = strtok_r(0, d, &lasts1)) {
    strcpy(inner, "blah:blat:blab:blag");

    for (tok2 = strtok_r(inner, d, &lasts2);
         tok2;
         tok2 = strtok_r(0, d, &lasts2)) {
      printf("|%s:%s|\n", tok1, tok2);
    }
  }
}

int
main(int argc, char **argv) {
  if (argc < 3) {
    printf("usage: string delimeter\n");
    return 1;
  }

  char *ss = argv[1];
  char *d = argv[2];
  test_strtok(ss, d);

  printf("----------\n");
  test_strtok_r();

  return 0;
}
