#include "../_algo_.h"
#include <errno.h>

#define M 20
#define N 23

#define H(x) ((x) % N)
#define H1(x) (((x) + 1) % N)
#define EMPTY 0

#ifndef FN_RD
#define FN_RD 0
#endif

#ifndef FN_LOC
#define FN_LOC 0
#endif

typedef int (*fn_read_t) (int *);
typedef int (*fn_probe_t) (int);

int read_number (int *);
int read_string (int *);
int insert (int, fn_probe_t, int *);
int find_loc_linear_probing (int);
int find_loc_quadratic_probing (int);
int find_loc_double_hashing (int);
void dump (void);

int hash_table[N + 1];

fn_read_t read_table[] = {
  read_number,
  read_string,
  (fn_read_t)0,
};

fn_probe_t probe_table[] = {
  find_loc_linear_probing,
  find_loc_quadratic_probing,
  find_loc_double_hashing,
  (fn_probe_t)0,
};

int
main (void)
{
  int n;
  int i = 0;
  memset (hash_table, EMPTY, sizeof (hash_table));

  while (read_table[FN_RD](&n) == 1)
    {
      if (insert (n, *probe_table[FN_LOC], &i))
        {
          perror ("!panic");
          break;
        }
    }

  dump ();

  return 0;
}

int
read_number (int *out)
{
  return scanf ("%d", out);
}

int
read_string (int *out)
{
  int h = 0;
  char buf[64], *p;
  int c = scanf ("%s", &buf[0]);
  if (c == 1)
    {
      for (p = &buf[0], h = 0; *p; p++)
        {
          h = *p + 31 * h;
        }
    }
  *out = h;
  return c;
}

int
insert (int key, fn_probe_t find_loc, int *n)
{
  int loc;

  loc = find_loc (key);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return -1;
    }

  if (hash_table[loc] == EMPTY)
    {
      (*n)++;
    }

  hash_table[loc] = key;

  return 0;
}

int
find_loc_linear_probing (int key)
{
  int loc = H (key);
  while (hash_table[loc] != EMPTY && hash_table[loc] != key)
    {
      loc = loc % N + 1;
    }
  return loc;
}

int
find_loc_quadratic_probing (int key)
{
  int i = 0;
  int loc = H (key);
  while (hash_table[loc] != EMPTY && hash_table[loc] != key)
    {
      i++;
      loc = loc + 2 * i + 3 * i * i;
      while (loc > N)
        {
          loc -= N;
        }
    }
  return loc;
}

int
find_loc_double_hashing (int key)
{
  int loc = H (key);
  int loc1 = H1 (key);
  while (hash_table[loc] != EMPTY && hash_table[loc] != key)
    {
      loc += loc1;
      if (loc > N)
        {
          loc -= N;
        }
    }
  return loc;
}

void
dump (void)
{
  int cnt = 0;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);
  for (size_t i = 0; i < total; i++)
    {
      if (hash_table[i] != EMPTY)
        {
          cnt++;
          printf ("%4zu  %4d\n", i, hash_table[i]);
        }
    }
  printf ("------------\ntable %d/(%d,%zu)\n", cnt, M, total);
}
