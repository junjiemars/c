#include <_os_.h>
#include <stdio.h>
#include <posix/getopt.h>

extern char *optarg;

void usage(const char *echo);

void
usage(const char *pcre)
{
  printf("Usage: %s [-n]... [string ...]\n", pcre);
	printf("\n");
	printf("Write arguments to the standard output.\n");
  printf("  -o            do not print the trailing newline character.\n");
}

int
main(int argc, char **argv)
{
  int opt_n;
  int ch;

  while (EOF != (ch = getopt(argc, argv, "hn")))
    {
      switch (ch)
        {
        case 'n':
          opt_n = 1;
          break;
        case 'h':
        default:
          usage(argv[0]);
          return 0;
        }
    }

  char **p = argv + optind;
  
  while (*p)
    {
      fprintf(stdout, "%s", *p++);
    }
  if (!opt_n)
    {
      fprintf(stdout, "\n");
    }

  return 0;
}
