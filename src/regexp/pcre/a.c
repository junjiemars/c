#include <_regexp_.h>
#include <string.h>
#include <stdio.h>
#include <pcre.h>

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  pcre *re;
  int options = 0;
  const char *errptr;
  int erroffset;
  
  const size_t N = 64;
  int ovector[N];
  int match = 0;
  const char *pattern = "ca*r";
  const char *subject = "caaar";
  
  re = pcre_compile(pattern, options, &errptr, &erroffset, 0);
  if (!re) {
    fprintf(stderr, "!panic, %s\n", errptr);
    return 1;
  }
  match = pcre_exec(re, 0, subject, strlen(subject), 0, options, ovector, N);
  if (match > 0) {
    for (int i = 0; i < match; i++) {
      fprintf(stderr, "%2d: %.*s\n",
              i,
              ovector[2*i+1] - ovector[2*i],
              subject + ovector[2*i]);
    }
    goto clean_exit;
  }

  switch (match) {
  case PCRE_ERROR_NOMATCH:
    fprintf(stderr, "no match\n");
    break;
    default:
      fprintf(stderr, "error while matching: %d\n", match);
      break;
  }

 clean_exit:
  pcre_free(re);
  return 0;
}
