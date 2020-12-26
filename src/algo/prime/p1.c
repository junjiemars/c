#include <_algo_.h>
#include <math.h>

#if (MSVC)
#  pragma warning(disable : 4996)
#endif

typedef int (*is_prime_fn)(int n);

int prime1(int n);
int prime2(int n);

void list_all_primes(int l, int r, is_prime_fn is_prime);

int
prime1(int n)
{
  for (int i = 2; i < n; i++)
    {
      if (n % i == 0)
        {
          return 0;
        }
    }
  return 1;
}

int
prime2(int n)
{
  for (int i = 2, r = (int)sqrt(n); i <= r; i++)
    {
      if (n % i == 0)
        {
          return 0;
        }
    }
  return 1;
}

void
list_all_primes(int l, int r, is_prime_fn is_prime)
{
  int p;
  for (int i = l; i < r; i++)
    {
      p = is_prime(i);
      if (p)
        {
          printf("%i, ", i);
        }
    }
  printf("\n");
}

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      printf("please, input range\n");
      return 0;
    }

  int l, r;
  sscanf(argv[1], "%i", &l);
  sscanf(argv[2], "%i", &r);

  printf("prime1\n------------\n");
  list_all_primes(l, r, prime1);

  printf("prime2\n------------\n");
  list_all_primes(l, r, prime2);
  
  return 0;
}
