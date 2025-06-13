#include <_regexp_.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  int flag;
  char const *name;
} RegFlagDef;

void usage (int cflags, int eflags, char const *cbuf, char const *ebuf);
int parse_reg_flags (char const *ss, int *flags, RegFlagDef const *, char *buf,
                     size_t bufsz);
int str_reg_flags (int flags, RegFlagDef const *def, char *buf, size_t bufsz);
int int_reg_flags (char const *ss, RegFlagDef const *def, int *flags);

void test (char const *pattern, char const *subject, int cflags,
           char const *cflags_str, int eflags, char const *eflags_str);

static struct option long_options[] = {
  { "help", no_argument, 0, 'h' },
  { "pattern", required_argument, 0, 'p' },
  { "subject", required_argument, 0, 's' },
  { "cflags", optional_argument, 0, 'c' },
  { "eflags", optional_argument, 0, 'e' },
  { 0, 0, 0, 0 },
};

static RegFlagDef reg_cflag_map[] = {
  { REG_BASIC, _str_ (REG_BASIC) },     { REG_EXTENDED, _str_ (REG_EXTENDED) },
  { REG_ICASE, _str_ (REG_ICASE) },     { REG_NOSUB, _str_ (REG_NOSUB) },
  { REG_NEWLINE, _str_ (REG_NEWLINE) }, { REG_NOSPEC, _str_ (REG_NOSPEC) },
  { REG_LITERAL, _str_ (REG_LITERAL) }, { REG_PEND, _str_ (REG_PEND) },
  { REG_MINIMAL, _str_ (REG_MINIMAL) }, { REG_UNGREEDY, _str_ (REG_UNGREEDY) },
  { REG_DUMP, _str_ (REG_DUMP) },       { REG_ENHANCED, _str_ (REG_ENHANCED) },
  { .flag = EOF, .name = NULL }
};

static RegFlagDef reg_eflag_map[]
    = { { REG_NOTBOL, _str_ (REG_NOTBOL) },
        { REG_NOTEOL, _str_ (REG_NOTEOL) },
        { REG_STARTEND, _str_ (REG_STARTEND) },
        { REG_TRACE, _str_ (REG_TRACE) },
        { REG_LARGE, _str_ (REG_LARGE) },
        { REG_BACKR, _str_ (REG_BACKR) },
        { REG_BACKTRACKING_MATCHER, _str_ (REG_BACKTRACKING_MATCHER) },
        { .flag = EOF, .name = NULL } };

int
main (int argc, char **argv)
{
  int ch;
  int cflags, eflags;
  char *pattern, *subject;
  char cbuf[BUFSIZ], ebuf[BUFSIZ];

  cflags = eflags = 0;
  pattern = subject = NULL;
  memset (cbuf, 0, sizeof (cbuf));
  memset (ebuf, 0, sizeof (ebuf));

  cflags |= REG_EXTENDED;
  cflags |= REG_ENHANCED;
  str_reg_flags (cflags, reg_cflag_map, cbuf, sizeof (cbuf));

  eflags |= REG_TRACE;
  str_reg_flags (eflags, reg_eflag_map, ebuf, sizeof (ebuf));

  if (argc < 2)
    {
      usage (cflags, eflags, cbuf, ebuf);
      goto clean_exit;
    }

  while (EOF != (ch = getopt_long (argc, argv, "hp:s:c:e:", long_options, 0)))
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
          parse_reg_flags (optarg, &cflags, reg_cflag_map, cbuf,
                           sizeof (cbuf));
          break;
        case 'e':
          parse_reg_flags (optarg, &eflags, reg_eflag_map, ebuf,
                           sizeof (ebuf));
          break;
        case 'h':
        default:
          usage (cflags, eflags, cbuf, ebuf);
          goto clean_exit;
        }
    }
  argc -= optind;
  argv += optind;

  test (pattern, subject, cflags, cbuf, eflags, ebuf);

clean_exit:
  free (pattern);
  free (subject);
  return 0;
}

void
usage (int cflags, int eflags, char const *cbuf, char const *ebuf)
{
  printf ("Usage: <pattern> <subject> [cflags] [eflags] [nmatch]\n");
  printf ("\n");
  printf ("Validate regexp pattern.\n");
  printf ("  -h, --help             print this message\n");
  printf ("  -p, --pattern          regexp pattern\n");
  printf ("  -s, --subject          subject\n");
  printf ("  -c, --cflags           cflags, default is %04o(%s)\n", cflags,
          cbuf);
  printf ("  -e, --eflags           eflags, default is %05o(%s)\n", eflags,
          ebuf);
}

int
parse_reg_flags (char const *ss, int *flags, RegFlagDef const *def, char *buf,
                 size_t bufsz)
{
  if (isalpha (ss[0]))
    {
      int_reg_flags (ss, def, flags);
    }
  else
    {
      str_reg_flags (*flags, def, buf, bufsz);
    }
  return 0;
}

int
str_reg_flags (int flags, RegFlagDef const *def, char *buf, size_t bufsz)
{
  size_t len = 0;

  for (RegFlagDef const *d = def; d->flag != EOF; d++)
    {
      if ((flags & d->flag) == d->flag)
        {
          len += snprintf (buf + len, bufsz - len, "%s|", d->name);
        }
    }

  if (buf && buf[len - 1] == '|')
    {
      buf[len - 1] = '\0';
    }

  return 0;
}

int
int_reg_flags (char const *ss, RegFlagDef const *def, int *flags)
{
  char s1[BUFSIZ];
  char const *d1 = "|";

  *flags = 0;
  memcpy (s1, ss, strlen (ss));

  for (char *tok = strtok (s1, d1); tok; tok = strtok (NULL, d1))
    {
      for (RegFlagDef const *d = def; d->flag != EOF; d++)
        {
          if (strcmp (tok, d->name) == 0)
            {
              *flags |= d->flag;
            }
        }
    }

  return 0;
}

void
test (char const *pattern, char const *string, int cflags,
      char const *cflags_str, int eflags, char const *eflags_str)
{
  int rc = 0;
  int err = 0;
  regex_t re = { 0 };
  regmatch_t *pmatch = NULL;
  char errbuf[BUFSIZ] = { 0 };
  char matbuf[BUFSIZ];

  printf ("----------\n"
          "pattern = '%s'\n"
          "string = '%s'\n"
          "cflags: %04o(%s)\n"
          "eflags: %05o(%s)\n"
          "----------\n",
          pattern, string, cflags, cflags_str ? cflags_str : "null", eflags,
          eflags_str ? eflags_str : "null");

  if ((rc = regcomp (&re, pattern, cflags)))
    {
      regerror (rc, &re, errbuf, sizeof (errbuf));
      fprintf (stderr, "!%s\n", errbuf);
      goto clean_exit;
    }

  if (!(pmatch = calloc (re.re_nsub + 1, sizeof (*pmatch))))
    {
      err = errno;
      fprintf (stderr, "!%s\n", strerror (err));
      goto clean_exit;
    }

  if ((rc = regexec (&re, string, re.re_nsub + 1, pmatch, eflags)))
    {
      regerror (rc, &re, errbuf, sizeof (errbuf));
      fprintf (stderr, "!%s\n", errbuf);
      goto clean_exit;
    }

  for (size_t i = 0; i < re.re_nsub + 1; i++)
    {
      regmatch_t const m = pmatch[i];
      memset (matbuf, 0, BUFSIZ);
      memcpy (matbuf, string + m.rm_so, m.rm_eo - m.rm_so);
      printf ("#%zu matched(%s): start = %i, end = %i\n", i, matbuf,
              (int)m.rm_so, (int)m.rm_eo);
    }

clean_exit:
  free (pmatch);
  regfree (&re);
}
