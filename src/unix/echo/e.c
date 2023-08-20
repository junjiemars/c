#include <_unix_.h>
#include <stdio.h>
#include <getopt.h>

extern char *optarg;
extern int   optind;

void usage (const char *echo);

void
usage (const char *pcre)
{
  printf ("Usage: %s [-n]... [string ...]\n", pcre);
	printf ("\n");
	printf ("Write arguments to the standard output.\n");
  printf ("  -n            do not print the trailing newline character.\n");
}

int
main (int argc, char **argv)
{
  int opt_n = 0;
  int ch;

  while (-1 != (ch = getopt(argc, argv, "hn")))
    {
      switch (ch)
        {
        case 'n':
          opt_n++;
          break;
        case 'h':
        default:
          usage (argv[0]);
          return 0;
        }
    }

  for (char **p = argv + optind; *p != 0; p++)
    {
      char sp = (optind == argc - 1) ? 0x0 : 0x20;
      fprintf (stdout, "%s%c", *p, sp);
    }

  if (!opt_n)
    {
      fprintf (stdout, "\n");
    }

  return 0;
}
