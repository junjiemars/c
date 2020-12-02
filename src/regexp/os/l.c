#include <_regexp_.h>
#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  if (argc < 3) {
    fprintf(stderr, "%s %s\n", "pattern", "subject");
    return 1;
  }
  
  regex_t re;
  int errcode = 0;
  size_t errbuf_size = 1024;
  char *errbuf;
  regmatch_t match;
  
  errbuf = calloc(errbuf_size, 1);
  if (!errbuf)
    {
      perror(NULL);
      return 0;
    }
  
  const char *pattern = argv[1];
  const char *subject = argv[2];
  
  errcode = regcomp(&re, pattern, REG_ICASE);
  if (errcode)
    {
      regerror(errcode, &re, errbuf, errbuf_size);
      fprintf(stderr, "%s\n", errbuf);
      return 0;
    }

  memset(&match, 0, sizeof(match));
  errcode = regexec(&re, subject, 0, &match, 0);
  if (REG_NOMATCH == errcode)
    {
      regerror(errcode, &re, errbuf, errbuf_size);
      fprintf(stderr, "%s\n", errbuf);
      return 0;
    }
  fprintf(stdout, "#matched\n");
    
  return 0;
}
