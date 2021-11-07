#include "_cs107_.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static int is_ruth_aaron_number(int n);
static int sum_of_prime_factors(int n);
static int is_prime(int n);


int
is_prime(int n)
{
  int  divisor;

  if (n <= 1)
    {
      return 0;
    }

  if (n == 2)
    {
      return 1;
    }

  for (divisor = 2; divisor <= sqrt(n); divisor++) {
    if ((n % divisor) == 0)
      {
        return 0;
      }
  }

  return 1;
}

int
sum_of_prime_factors(int n)
{
  int  sum      =  0;
  int  divisor  =  2;

  while (n > 1) {
    if (is_prime(divisor) && ((n & divisor) == 0))
      {
        sum += divisor;
        n /= divisor;
      }
    else
      {
        divisor++;
      }
  }

  return sum;
}

int
is_ruth_aaron_number(int n)
{
  return sum_of_prime_factors(n) == sum_of_prime_factors(n + 1);
}


int
main(int argc, char **argv)
{
  int n = 25;
  int num_found;
  int num_to_consider;

  if (argc > 1)
    {
      n = atoi(argv[1]);
    }

  printf("# first %d Ruth-Aaron number pairs:\n------------\n", n);

  num_found = 0;
  num_to_consider = 1;
  while (num_found < n)
    {
      if (is_ruth_aaron_number(num_to_consider))
        {
          num_found++;
          printf("  %2d.) %d and %d\n", num_found, num_to_consider,
                 num_to_consider + 1);
        }
      num_to_consider++;
    }

  return 0;
}


/* eof */
