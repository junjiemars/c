#include <_regexp_.h>
#include <posix/getopt.h>
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

void usage (void);

void run_auto_test (void);

int test_bone (const char *pattern, const char *subject, int cflags,
               int eflags, size_t nmatch, regmatch_t *matches, size_t *re_nsub,
               size_t errbuf_size, char *errbuf);

void test_basic (const char *pattern, const char *subject, int cflags,
                 const char *cflags_str, int eflags, const char *eflags_str,
                 int nmatch);

static struct option long_options[] = {
  { "help", no_argument, 0, 'h' },
  { "pattern", required_argument, 0, 'p' },
  { "subject", required_argument, 0, 's' },
  { "cflags", optional_argument, 0, 'c' },
  { "eflags", optional_argument, 0, 'e' },
  { "nmatch", optional_argument, 0, 'n' },
  { 0, 0, 0, 0 },
};

int
main (__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv)
{
  if (argc < 2)
    {
      run_auto_test ();
    }
  else
    {
      int ch;
      int cflags, eflags, nmatch;
      char *pattern, *subject;

      cflags = eflags = nmatch = 0;
      pattern = subject = NULL;

      while (
          EOF
          != (ch = getopt_long (argc, argv, "hp:s:c:e:n:", long_options, 0)))
        {
          switch (ch)
            {
            case 'p':
              pattern = strdup (optarg);
              break;
            case 's':
              subject = strdup (optarg);
              break;
            case 'c':
              cflags = atoi (optarg);
              break;
            case 'e':
              eflags = atoi (optarg);
              break;
            case 'n':
              nmatch = atoi (optarg);
              break;
            case 'h':
            default:
              usage ();
            }
        }
      argc -= optind;
      argv += optind;

      test_basic (pattern, subject, cflags, NULL, eflags, NULL, nmatch);
    }

  return 0;
}

void
usage (void)
{
  printf ("Usage: <pattern> <subject> [cflags] [eflags] [nmatch]\n");
  printf ("\n");
  printf ("Validate regexp pattern.\n");
  printf ("  -h, --help             print this message\n");
  printf ("  -p, --pattern          regexp pattern\n");
  printf ("  -s, --subject          subject\n");
  printf ("  -c, --cflags           cflags, default is 0\n");
  printf ("  -e, --eflags           eflags, default is 0\n");
  printf ("  -n, --nmatch           nmatch, default is 0\n");
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
          "pattern = %s\n"
          "subject = '%s'\n"
          "nmatch: %d\n"
          "cflags: %d%s\n"
          "eflags: %d%s\n"
          "----------\n",
          pattern, subject, nmatch, cflags, cflags_str, eflags, eflags_str);

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
