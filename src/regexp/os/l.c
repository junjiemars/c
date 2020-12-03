#include <_regexp_.h>
#if LINUX
#  include <sys/types.h>
#endif
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef REG_BASIC
#  define REG_BASIC 0
#endif

#define ERRBUF_SIZE 1024
static char errbuf[ERRBUF_SIZE];

int
test_bone(const char *pattern,
          const char *subject,
          int cflags,
          int eflags,
          size_t nmatch,
          regmatch_t *matches,
          size_t errbuf_size,
          char *errbuf)
{
  int errcode = 0;
  regex_t re;
  
  errcode = regcomp(&re, pattern, cflags);
  if (errcode)
    {
      regerror(errcode, &re, errbuf, errbuf_size);
      return errcode;
    }

  errcode = regexec(&re, subject, nmatch, matches, eflags);
  if (REG_NOMATCH == errcode)
    {
      regerror(errcode, &re, errbuf, errbuf_size);
      goto clean_exit;
    }

 clean_exit:
  regfree(&re);
  return errcode;
}

void
test_basic(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 1;
  regmatch_t match;

  printf("----------\n"
         "cflags: REG_BASIC\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = '%s'\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone(pattern,
                      subject,
                      REG_BASIC,
                      0,
                      nmatch,
                      &match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  strncpy(errbuf, subject + match.rm_so, match.rm_eo - match.rm_so);
  printf("matched(%s): start = %i, end = %i\n",
         errbuf,
         (int)match.rm_so,
         (int)match.rm_eo);
}

void
test_ignore_case(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 1;
  regmatch_t match;

  printf("----------\n"
         "cflags: REG_ICASE\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = %s\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone(pattern,
                      subject,
                      REG_ICASE,
                      0,
                      nmatch,
                      &match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  strncpy(errbuf, subject + match.rm_so, match.rm_eo - match.rm_so);
  printf("matched(%s): start = %i, end = %i\n",
         errbuf,
         (int)match.rm_so,
         (int)match.rm_eo);
}

void
test_no_report_matches(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 1;
  regmatch_t match;

  printf("----------\n"
         "cflags: REG_NOSUB\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = %s\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone(pattern,
                      subject,
                      REG_NOSUB,
                      0,
                      nmatch,
                      &match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  strncpy(errbuf, subject + match.rm_so, match.rm_eo - match.rm_so);
  printf("matched(%s): start = %i, end = %i\n",
         errbuf,
         (int)match.rm_so,
         (int)match.rm_eo);
}

void
test_newline(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 1;
  regmatch_t match;

  printf("----------\n"
         "cflags: REG_NEWLINE\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = '%s'\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone(pattern,
                      subject,
                      REG_NEWLINE,
                      REG_NOTBOL | REG_NOTEOL,
                      nmatch,
                      &match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  strncpy(errbuf, subject + match.rm_so, match.rm_eo - match.rm_so);
  printf("matched(%s): start = %i, end = %i\n",
         errbuf,
         (int)match.rm_so,
         (int)match.rm_eo);
}

void
test_extended(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 1;
  regmatch_t match;

  printf("----------\n"
         "cflags: REG_EXTENDED\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = '%s'\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone(pattern,
                      subject,
                      REG_EXTENDED,
                      0,
                      nmatch,
                      &match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      return;
    }

  strncpy(errbuf, subject + match.rm_so, match.rm_eo - match.rm_so);
  printf("matched(%s): start = %i, end = %i\n",
         errbuf,
         (int)match.rm_so,
         (int)match.rm_eo);
}

void
test_group(const char *pattern, const char *subject)
{
  int errcode = 0;
  int nmatch = 4;
  regmatch_t *match;

  printf("----------\n"
         "cflags: REG_EXTENDED\n"
         "eflags: 0\n"
         "pattern = %s\n"
         "subject = '%s'\n"
         "----------\n",
         pattern, subject);

  memset(errbuf, 0, ERRBUF_SIZE);
  match = calloc(nmatch + 1, sizeof(*match));
  
  errcode = test_bone(pattern,
                      subject,
                      REG_EXTENDED,
                      0,
                      nmatch,
                      match,
                      ERRBUF_SIZE,
                      errbuf);
  if (errcode)
    {
      fprintf(stderr, "%s\n", errbuf);
      goto clean_exit;
    }

  for (int i = 0; i < nmatch; i++)
    {
      const regmatch_t *m = &match[i];
      if (m->rm_so < 0 || m->rm_eo < 0)
        {
          break;
        }
      memset(errbuf, 0, ERRBUF_SIZE);
      strncpy(errbuf, subject + m->rm_so, m->rm_eo - m->rm_so);
      printf("matched(%s): start = %i, end = %i\n",
             errbuf,
             (int)m->rm_so,
             (int)m->rm_eo);
    }
  
 clean_exit:
  free(match);
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_basic("car", "caaar");
  test_basic("ca*r", "caaar");
  test_basic("ca*r", "acaaar");

  test_basic("ca*r", "CAAAR");
  test_ignore_case("ca*r", "CAAAR");

  test_no_report_matches("ca*r", "acaaar");

  test_basic("^ca*r", "\ncaaar");
  test_basic("ca*r$", "caaar\n");
  test_newline("^ca*r$", "\ncaaar\n");

  test_basic("c[abc]+r", "caaar");
  test_extended("c[abc]+r", "caaar");

  test_group("abc(Ca*r|Tru*ck)?", "abcTruuuck");

  return 0;
}
