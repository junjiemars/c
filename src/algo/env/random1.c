#include "../_algo_.h"
#include <math.h>
#include <stdlib.h>

static void calc (int, int, int);
static int int_rand (int);
static int double_rand (int);

int
main (int argc, char **argv)
{
  int rs[] = { 10, 100, 1000, 2, 4, 16 };
  int ns[] = { 1000, 10000, 100000, 1000000 };
  int mode = 0; /* int, otherwise double */

  if (argc > 1)
    {
      mode = atoi (argv[1]);
    }

  srand (time (NULL));

  for (int r = 0; r < (int)_nof_ (rs); r++)
    {
      for (int n = 0; n < (int)_nof_ (ns); n++)
        {
          calc (rs[r], ns[n], mode);
        }
    }

  return 0;
}

void
calc (int r, int n, int mode)
{
  double sum = 0.0, sum_square = 0.0;
  double average, std_derivation;

  for (int i = 0; i < n; i++)
    {
      int r1 = mode ? double_rand (r) : int_rand (r);
      sum += r1;
      sum_square += (double)r1 * r1;
    }

  average = sum / n;
  std_derivation = (sum_square / n) - (average * average);

  printf ("%4d %7d %10lf %12lf\n", r, n, average, std_derivation);
}

int
int_rand (int r)
{
  return rand () % r;
}

int
double_rand (int r)
{
  double r1 = 1.0 * rand () / RAND_MAX;
  return (int)(r1 * r);
}
