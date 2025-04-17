#include <_algo_.h>

static int fibo1 (int);
static int fibo2 (int, int, int);
static int fibo3 (int, int, int);
static int fibo4 (int);

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      printf ("fibonacci(n)\n");
      return 1;
    }

  int n = atoi (argv[1]);

  printf ("fibo1(%i) = %i\n", n, fibo1 (n));
  printf ("fibo2(%i) = %i\n", n, fibo2 (n, 0, 1));
  printf ("fibo3(%i) = %i\n", n, fibo3 (n, 0, 1));
  printf ("fibo4(%i) = %i\n", n, fibo4 (n));

  return 0;
}

int
fibo1 (int n)
{
  if (0 == n || 1 == n)
    {
      return 1;
    }

  return fibo1 (n - 1) + fibo1 (n - 2);
}

int
fibo2 (int n, int p, int acc)
{
  if (0 == n)
    {
      return acc;
    }

  return fibo2 (n - 1, acc, p + acc);
}

int
fibo3 (int n, int p, int acc)
{
  int t;

  while (n-- > 0)
    {
      t = p;
      p = acc;
      acc = t + p;
    }

  return acc;
}

int
fibo4 (int n)
{
  int t;
  int p = 0, acc = 1;

  while (n-- > 0)
    {
      t = p;
      p = acc;
      acc = t + p;
    }

  return acc;
}
