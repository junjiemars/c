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

void usage (int, int, char const *, char const *);
void dump_flags (RegFlagDef const *, int);
int parse_reg_flags (char const *, int *, RegFlagDef const *);
int str_reg_flags (int, RegFlagDef const *, char *, size_t);
void test (char const *, char const *, int, char const *, int, char const *);

static struct option long_options[] = {
  { "help", no_argument, 0, 'h' },
  { "pattern", required_argument, 0, 'p' },
  { "subject", required_argument, 0, 's' },
  { "cflags", optional_argument, 0, 'c' },
  { "eflags", optional_argument, 0, 'e' },
  { "dump", no_argument, 0, 'd' },
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
  int opt_dump = 0;
  int cflags = 0, eflags = 0;
  char *pattern = NULL, *subject = NULL;
  char *opt_cflag = NULL, *opt_eflag = NULL;
  char cbuf[BUFSIZ], ebuf[BUFSIZ];

  memset (cbuf, 0, sizeof (cbuf));
  memset (ebuf, 0, sizeof (ebuf));
  cflags |= REG_EXTENDED;
  cflags |= REG_ENHANCED;
  eflags |= REG_TRACE;

  if (argc < 2)
    {
      usage (cflags, eflags, cbuf, ebuf);
      goto clean_exit;
    }

  while (EOF != (ch = getopt_long (argc, argv, "hdp:s:c:e:", long_options, 0)))
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
          opt_cflag = strdup (optarg);
          break;
        case 'e':
          opt_eflag = strdup (optarg);
          break;
        case 'd':
          opt_dump++;
          break;
        case 'h':
        default:
          usage (cflags, eflags, cbuf, ebuf);
          goto clean_exit;
        }
    }
  argc -= optind;
  argv += optind;

  if (opt_dump)
    {
      if (opt_cflag)
        {
          dump_flags (reg_cflag_map, 4);
        }
      if (opt_eflag)
        {
          dump_flags (reg_eflag_map, 5);
        }
      goto clean_exit;
    }

  if (opt_cflag)
    {
      parse_reg_flags (opt_cflag, &cflags, reg_cflag_map);
    }
  if (opt_eflag)
    {
      parse_reg_flags (opt_eflag, &eflags, reg_eflag_map);
    }
  str_reg_flags (eflags, reg_eflag_map, ebuf, sizeof (ebuf));
  str_reg_flags (cflags, reg_cflag_map, cbuf, sizeof (cbuf));

  test (pattern, subject, cflags, cbuf, eflags, ebuf);

clean_exit:
  free (opt_cflag);
  free (opt_eflag);
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
  printf ("  -d, --dump-flags      dump all cflags and eflags\n");
}

void
dump_flags (RegFlagDef const *map, int width)
{
  char fmt[64];
  snprintf (fmt, sizeof (fmt), "%%0%do %%-20s\n", width);
  for (RegFlagDef const *d = map; d && d->flag != EOF; d++)
    {
      printf (fmt, d->flag, d->name);
    }
}

int
parse_reg_flags (char const *ss, int *flags, RegFlagDef const *def)
{
  char s1[BUFSIZ];
  char const *d1 = "|";

  *flags = 0;
  strcpy (s1, ss);

  for (char *tok = strtok (s1, d1); tok; tok = strtok (NULL, d1))
    {
      for (RegFlagDef const *d = def; d->flag != EOF; d++)
        {
          if (isnumber (*tok))
            {
              int oct = atoi (tok);
              if (oct == d->flag)
                {
                  *flags |= d->flag;
                  continue;
                }
            }
          else if (isalpha (*tok))
            {
              if (strcmp (tok, d->name) == 0)
                {
                  *flags |= d->flag;
                  continue;
                }
            }
        }
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

void
test (char const *pattern, char const *string, int cflags,
      char const *cflags_str, int eflags, char const *eflags_str)
{
  int rc = 0;
  int err = 0;
  size_t len;
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
      len = regerror (rc, &re, errbuf, sizeof (errbuf));
      assert (len <= sizeof (errbuf) && "errbuf too small");
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
      len = regerror (rc, &re, errbuf, sizeof (errbuf));
      assert (len <= sizeof (errbuf) && "errbuf too small");
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
