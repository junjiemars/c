#include <_algo_.h>
#include "prime.h"
#include <math.h>

int *
new_prime (__attribute__ ((unused)) int l, int r)
{
  int *a = calloc (r, sizeof (int));
  assert (a != NULL);
  return a;
}

/**
 * sieve of Eratosthenes, 300B.C
 */
void
prime_sieve (int l, int r, int *a)
{
  int i, j;
  l = 2; /* alway from 2 */

  for (i = l; i < r; i++)
    {
      a[i] = 1;
    }

  for (i = l; i < r; i++)
    {
      if (a[i])
        {
          for (j = i; i * j < r; j++)
            {
              a[i * j] = 0;
            }
        }
    }
}

void
prime_print (int l, int r, int *a)
{
  for (int i = l, j = 8; i < r; i++)
    {
      if (a[i])
        {
          printf ("%6d ", i);
          if (!--j)
            {
              printf ("\n");
              j = 8;
            }
        }
    }
  if ((r - l) % 8)
    {
      printf ("\n");
    }
}

bool
prime_check (int a)
{
  for (int i = 2, r = (int)sqrt (a); i <= r; i++)
    {
      if (a % i == 0)
        {
          return false;
        }
    }
  return true;
}
