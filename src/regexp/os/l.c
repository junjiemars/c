#include <_regexp_.h>
#if LINUX
#  include <sys/types.h>
#endif
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERRBUF_SIZE 1024
static char errbuf[ERRBUF_SIZE];

void
test_basic(const char *pattern, const char *subject)
{
  regex_t re;
  int errcode = 0;
  regmatch_t match;

  printf("----------\npattern = %s\nsubject = %s\n----------\n",
         pattern, subject);
  
  errcode = regcomp(&re, pattern, REG_BASIC);
  if (errcode)
    {
      regerror(errcode, &re, errbuf, ERRBUF_SIZE);
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  memset(&match, 0, sizeof(match));
  errcode = regexec(&re, subject, 0, &match, 0);
  if (REG_NOMATCH == errcode)
    {
      regerror(errcode, &re, errbuf, ERRBUF_SIZE);
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  printf("Matched: start = %i, end = %i\n",
         (int)match.rm_so,
         (int)match.rm_eo);
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_basic("ca*r", "caaar");
    
  return 0;
}
