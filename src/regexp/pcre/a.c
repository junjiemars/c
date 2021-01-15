#include <_regexp_.h>
#include <stdio.h>
#include <pcre.h>
#include <posix/getopt.h>
#include <string.h>

#define N 64
extern char *optarg;
extern int errno;

void usage(const char *pcre);
int regexp(const char *pattern, const char *subject, int options);

static struct option long_options[] =
  {
    {"help",    no_argument,         0, 'h'},
    {"pattern", required_argument,   0, 'p'},
    {"subject", required_argument,   0, 's'},
    {"options", optional_argument,   0, 'o'},
    {0,         0,                   0,  0 },
  };

void
usage(const char *pcre)
{
  printf("Usage: %s [OPTION]... [SUBJECT]...\n", pcre);
	printf("\n");
	printf("Validate regexp pattern via libpcre.\n");
	printf("  -h, --help             print this message\n");
	printf("  -p, --pattern          regexp pattern\n");
	printf("  -s, --subject          subject\n");
  printf("  -o, --options          pcre options, default is 0\n");
}

int
regexp(const char *pattern, const char *subject, int options)
{
  int has_error = 0;
  pcre *re = 0;
  const char **errptr;
  int erroffset;
  int *ovector = 0;
  int match = 0;

  errptr = malloc(N);
  if (!errptr)
    {
      has_error = errno;
      perror(0);
      goto clean_exit;
    }

  ovector = malloc(N * 2);
  if (!ovector)
    {
      has_error = errno;
      perror(0);
      goto clean_exit;
    }

  re = pcre_compile(pattern, options, errptr, &erroffset, 0);
  if (!re)
    {
      has_error = errno;
      fprintf(stderr, "!panic, %s\n", *errptr);
      goto clean_exit;
    }
  match = pcre_exec(re,
                    0,
                    subject,
                    strnlen(subject, N),
                    0,
                    options,
                    ovector,
                    N);
  if (match > 0)
    {
      for (int i = 0; i < match; i++)
        {
          fprintf(stderr, "%2d: %.*s\n",
                  i,
                  ovector[2*i+1] - ovector[2*i],
                  subject + ovector[2*i]);
        }
      goto clean_exit;
    }

  switch (match)
    {
    case PCRE_ERROR_NOMATCH:
      fprintf(stderr, "no match\n");
      break;
    default:
      fprintf(stderr, "error while matching: %d\n", match);
      break;
    }

 clean_exit:
  free(ovector);
  pcre_free(re);
  return has_error;
}

int
main(int argc, char **argv)
{
  int opt_options = 0;
  char *opt_pattern = 0;
  char *opt_subject = 0;

  int has_error = 0;
  int ch;

  while (EOF != (ch = getopt_long(argc, argv, "hp:s:o:", long_options, 0)))
    {
      switch (ch) {
      case 'h':
        usage(argv[0]);
        goto clean_exit;
      case 'p':
        {
          size_t n = strnlen(optarg, N) + 1;
          opt_pattern = malloc(n);
          if (!opt_pattern)
            {
              has_error = errno;
              perror(0);
              goto clean_exit;
            }
          strncpy(opt_pattern, optarg, n);
        }
        break;
      case 's':
        {
          size_t n = strnlen(optarg, N) + 1;
          opt_subject = malloc(n);
          if (!opt_subject)
            {
              has_error = errno;
              perror(0);
              goto clean_exit;
            }
          strncpy(opt_subject, optarg, n);
        }
        break;
      case 'o':
        {
          sscanf(optarg, "%i", &opt_options);
        }
        break;
      default:
        usage(argv[0]);
        goto clean_exit;
      }
    }

  has_error = regexp(opt_pattern, opt_subject, opt_options);

 clean_exit:
  free(opt_pattern);
  free(opt_subject);
  return has_error;
}
