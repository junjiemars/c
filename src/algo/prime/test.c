#include "../_algo_.h"
#include "prime.h"
#include <getopt.h>

#if (MSVC)
#pragma warning(disable : 4996)
#endif

static void usage (void);
static void test_prime_sieve (int, int);
static void test_prime_check (int);

int
main (int argc, char **argv)
{
  int ch;
  int opt_lower = 2, opt_upper = 0, opt_check = 0;
  while ((ch = getopt (argc, argv, "hc:l:")) != -1)
    {
      switch (ch)
        {
        case 'c':
          if (sscanf (optarg, "%i", &opt_check) != 1)
            {
              fprintf (stderr, "!panic, illegal `-c %s'\n", optarg);
              exit (1);
            }
          break;
        case 'l':
          if (sscanf (optarg, "%i,%i", &opt_lower, &opt_upper) != 2)
            {
              fprintf (stderr, "!panic, illegal `-l %s'\n", optarg);
              exit (1);
            }
          break;
        case 'h':
          usage ();
          exit (0);
        default:
          usage ();
          exit (1);
        }
    }
  argc -= optind;
  argv += optind;

  if (opt_check)
    {
      test_prime_check (opt_check);
    }
  else if (opt_upper)
    {
      if (opt_lower < 2)
        {
          opt_lower = 2;
        }
      test_prime_sieve (opt_lower, opt_upper);
    }

  return 0;
}

void
usage (void)
{
  fprintf (stderr, "Usage: [-h|-c<num>|-lnum,num]\n");
}

void
test_prime_sieve (int l, int r)
{
  int *a = new_prime (l, r);
  prime_sieve (l, r, a);
  prime_print (l, r, a);
}

void
test_prime_check (int a)
{
  printf ("%d\n", prime_check (a));
}
