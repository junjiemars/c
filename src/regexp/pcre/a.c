#include <_regexp_.h>
#include <stdio.h>
#include <pcre.h>
#include <posix/getopt.h>
#include <string.h>

#define N 64
extern char *optarg;

void usage(const char *pcre);

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

static struct option long_options[] =
  {
    {"help",    no_argument,         0, 'h'},
    {"pattern", required_argument,   0, 'p'},
    {"subject", required_argument,   0, 's'},
    {"options", optional_argument,   0, 'o'},
    {0,         0,                   0,  0 },
  };

int
main(int argc, char **argv)
{
  pcre *re = 0;
  const char *errptr;
  int erroffset;
  int *ovector = 0;
  int match = 0;

  int opt_options = 0;
  char *opt_pattern = 0;
  char *opt_subject = 0;

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

  ovector = malloc(N * 2);
  if (!ovector)
    {
      perror(0);
      goto clean_exit;
    }

  re = pcre_compile(opt_pattern, opt_options, &errptr, &erroffset, 0);
  if (!re)
    {
      fprintf(stderr, "!panic, %s\n", errptr);
      goto clean_exit;
    }
  match = pcre_exec(re, 0, opt_subject, strnlen(opt_subject, N), 0, opt_options, ovector, N);
  if (match > 0)
    {
      for (int i = 0; i < match; i++)

        {
          fprintf(stderr, "%2d: %.*s\n",
                  i,
                  ovector[2*i+1] - ovector[2*i],
                  opt_subject + ovector[2*i]);
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
  free(opt_pattern);
  free(opt_subject);
  free(ovector);
  pcre_free(re);

  return 0;
}
