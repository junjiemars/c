#include <_regexp_.h>
/* #include <posix/getopt.h> */
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef REG_BASIC
#define REG_BASIC 0
#endif

#define ERRBUF_SIZE 512

static char errbuf[ERRBUF_SIZE];
static char matbuf[ERRBUF_SIZE];

void run_auto_test (void);

int test_bone (const char *pattern, const char *subject, int cflags,
               int eflags, size_t nmatch, regmatch_t *matches, size_t *re_nsub,
               size_t errbuf_size, char *errbuf);

void test_basic (const char *pattern, const char *subject, int cflags,
                 const char *cflags_str, int eflags, const char *eflags_str,
                 int nmatch);

int
main (__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv)
{
  if (argc < 2)
    {
      run_auto_test ();
    }
  else
    {
      fprintf (stderr,
               "usage: <pattern> <subject> [cflags] [eflags] [nmatch]\n");
      return 1;
    }

  return 0;
}

void
run_auto_test (void)
{
  test_basic ("car", "caaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0), 0);
  test_basic ("ca*r", "caaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0), 1);
  test_basic ("ca*r", "acaaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0), 1);

  test_basic ("ca*r", "CAAAR", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0), 1);
  test_basic ("ca*r", "CAAAR", REG_ICASE, _str_ (REG_ICASE), 0, _str_ (0), 1);

  test_basic ("ca*r", "acaaar", REG_NOSUB, _str_ (REG_NOSUB), 0, _str_ (0), 1);
  test_basic ("ca*r", "acaaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0), 0);

  test_basic ("^ca*r", "\ncaaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0),
              1);
  test_basic ("ca*r$", "caaar\n", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0),
              1);
  test_basic ("^ca*r$", "\ncaaar\n", REG_NEWLINE, _str_ (REG_NEWLINE), 0,
              _str_ (0), 1);

  test_basic ("c[abc]+r", "caaar", REG_BASIC, _str_ (REG_BASIC), 0, _str_ (0),
              1);
  test_basic ("c[abc]+r", "caaar", REG_EXTENDED, _str_ (REG_EXTENDED), 0,
              _str_ (0), 1);

  test_basic ("abc(Ca*r|Tru*ck)?", "abcTruuuck", REG_EXTENDED,
              _str_ (REG_EXTENDED), 0, _str_ (0), 2);
}

int
test_bone (const char *pattern, const char *subject, int cflags, int eflags,
           size_t nmatch, regmatch_t *pmatch, size_t *re_nsub,
           size_t errbuf_size, char *errbuf)
{
  int errcode = 0;
  regex_t re;

  errcode = regcomp (&re, pattern, cflags);
  if (errcode)
    {
      regerror (errcode, &re, errbuf, errbuf_size);
      return errcode;
    }

  errcode = regexec (&re, subject, nmatch, pmatch, eflags);
  if (errcode)
    {
      regerror (errcode, &re, errbuf, errbuf_size);
      goto clean_exit;
    }
  *re_nsub = re.re_nsub;

clean_exit:
  regfree (&re);
  return errcode;
}

void
test_basic (const char *pattern, const char *subject, int cflags,
            const char *cflags_str, int eflags, const char *eflags_str,
            int nmatch)
{
  int errcode = 0;
  size_t nsub = 0;
  regmatch_t *match = NULL;

  printf ("----------\n"
          "cflags: %s\n"
          "eflags: %s\n"
          "pattern = %s\n"
          "subject = '%s'\n"
          "----------\n",
          cflags_str, eflags_str, pattern, subject);

  match = calloc (nmatch + 1, sizeof (*match));
  memset (errbuf, 0, ERRBUF_SIZE);

  errcode = test_bone (pattern, subject, cflags, eflags, nmatch, match, &nsub,
                       ERRBUF_SIZE, errbuf);
  if (errcode)
    {
      fprintf (stdout, "%s\n", errbuf);
      goto clean_exit;
    }

  for (size_t i = 0; i <= nsub; i++)
    {
      const regmatch_t m = match[i];
      memset (matbuf, 0, ERRBUF_SIZE);
      strncpy (matbuf, subject + m.rm_so, m.rm_eo - m.rm_so);
      printf ("matched(%s): start = %i, end = %i\n", matbuf, (int)m.rm_so,
              (int)m.rm_eo);
    }

clean_exit:
  free (match);
}
