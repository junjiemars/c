#include "../_algo_.h"
#include <errno.h>

#define M 20
#define N 23

#define EMPTY 0

int hash (int);
int insert (int);
void dump (void);

int table[N + 1] = { EMPTY };
int count = 0;

int
main (void)
{
  int n;
  int i = 0;

  while (scanf ("%d", &n) == 1)
    {
      insert (n);
      i++;
    }

  dump ();

  return 0;
}

int
hash (int n)
{
  return n % N + 1;
}

int
insert (int n)
{
  int h;
  static int count = 0;

  h = hash (n);

  while (table[h] != EMPTY && table[h] == n)
    {
      h = hash (h);
    }

  if (count >= M)
    {
      return EOVERFLOW;
    }

  count++;
  table[h] = n;

  return 0;
}

void
dump (void)
{
  int cnt = 0;
  size_t total = sizeof (table) / sizeof (table[0]);

  for (size_t i = 0; i < total; i++)
    {
      if (table[i] != EMPTY)
        {
          cnt++;
          printf ("%4zu  %4d\n", i, table[i]);
        }
    }
  printf ("------------\ntable (%d/%zu)\n", cnt, total);
}
