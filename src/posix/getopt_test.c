#include "ndef.h"
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#if (MSVC)
#  pragma warning(disable:4996)
#endif


#define OPT_REQUIRED_MAX  256


static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "r",       required_argument,    0,              'r' },
    { "o",       optional_argument,    0,              'o' },
    { "n",       no_argument,          0,              'n' },
    { "N",       no_argument,          0,              'N' },
    { 0,         0,                    0,               0  }
  };

static char opt_required[OPT_REQUIRED_MAX] = {0};
static int opt_optional = 0;
static int opt_no = 0;


static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help         this help text\n");
  printf("  -r, --required     required argument\n");
  printf("  -o, --optional     optional argument, default is %d\n",
         opt_optional);
  printf("  -n  --no-argument  no argument, default is %d\n", opt_no);
  printf("  -N, --negate       negate -n option\n");
}


int
main(int argc, char **argv)
{
  int  ch;

  if (1 == argc)
    {
      usage(argv[0]);
      goto clean_exit;
    }

  while (-1 != (ch = getopt_long(argc, argv,
                                 "hr:o:nN",
                                 longopts, 0)))
    {
      switch (ch)
        {
        case 'r':
          strcpy(opt_required, optarg);
          break;
        case 'o':
          opt_optional = atoi(optarg);
          break;
        case 'n':
          opt_no = 1;
          break;
        case 'N':
          opt_no = !opt_no;
          break;
        default:
          usage(argv[0]);
          goto clean_exit;
        }
    }

  fprintf(stdout, "# command line options:\n"
          " -> --required=%s --optional=%d --no=%d\n",
          &opt_required[0], opt_optional, opt_no);

 clean_exit:
  return 0;
}
