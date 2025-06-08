#include <_regex.h>
#include <_regexp_.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage (void);

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

static char errbuf[BUFSIZ];
static char matbuf[BUFSIZ];

int
main (int argc, char **argv)
{
  int ch;
  int cflags, eflags, nmatch;
  char *pattern, *subject;

  cflags = eflags = nmatch = 0;
  pattern = subject = NULL;

  if (argc < 2)
    {
      usage ();
      goto clean_exit;
    }

  while (EOF
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
          goto clean_exit;
        }
    }
  argc -= optind;
  argv += optind;

  if (cflags == 0)
    {
      cflags |= REG_EXTENDED;
#ifdef __APPLE__
      cflags |= REG_ENHANCED;
#endif
    }

  if (eflags == 0)
    {
      eflags |= REG_TRACE;
    }

  test_basic (pattern, subject, cflags, NULL, eflags, NULL, nmatch);

clean_exit:
  free (pattern);
  free (subject);
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
  printf ("  -s, --string           string\n");
  printf ("  -c, --cflags           cflags, default is 0001\n");
  printf ("  -e, --eflags           eflags, default is 00400\n");
  printf ("  -n, --nmatch           nmatch, default is 0\n");
}

int
test_bone (const char *pattern, const char *string, int cflags, int eflags,
           size_t nmatch, regmatch_t *pmatch, size_t *re_nsub,
           size_t errbuf_sz, char *errbuf)
{
  int rc = 0;
  regex_t re;

  rc = regcomp (&re, pattern, cflags);
  if (rc)
    {
      regerror (rc, &re, errbuf, errbuf_sz);
      return rc;
    }

  rc = regexec (&re, string, nmatch, pmatch, eflags);
  if (rc)
    {
      regerror (rc, &re, errbuf, errbuf_sz);
      goto clean_exit;
    }
  *re_nsub = re.re_nsub;

clean_exit:
  regfree (&re);
  return rc;
}

void
test_basic (const char *pattern, const char *string, int cflags,
            const char *cflags_str, int eflags, const char *eflags_str,
            int nmatch)
{
  int rc = 0;
  size_t nsub = 0;
  regmatch_t *pmatch = NULL;

  printf ("----------\n"
          "pattern = '%s'\n"
          "string = '%s'\n"
          "nmatch: %d\n"
          "cflags: %04d(%s)\n"
          "eflags: %04d(%s)\n"
          "----------\n",
          pattern, string, nmatch, cflags, cflags_str ? cflags_str : "null",
          eflags, eflags_str ? eflags_str : "null");

  pmatch = calloc (nmatch + 1, sizeof (*pmatch));
  memset (errbuf, 0, BUFSIZ);

  rc = test_bone (pattern, string, cflags, eflags, nmatch, pmatch, &nsub,
                  BUFSIZ, errbuf);
  if (rc)
    {
      fprintf (stdout, "%s\n", errbuf);
      goto clean_exit;
    }

  for (size_t i = 0; i < nsub; i++)
    {
      regmatch_t const m = pmatch[i];
      memset (matbuf, 0, BUFSIZ);
      strncpy (matbuf, string + m.rm_so, m.rm_eo - m.rm_so);
      printf ("#%zu matched(%s): start = %i, end = %i\n", i, matbuf,
              (int)m.rm_so, (int)m.rm_eo);
    }

clean_exit:
  free (pmatch);
}
