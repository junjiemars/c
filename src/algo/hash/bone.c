#include "../_algo_.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

#if !defined(M) || (M < 1)
#define M 20
#endif

#if !defined(N) || (N < M - 3)
#define N (M + 3)
#endif

#define H(x) ((x) % N)
#define H2(x) (((x) + 1) % N)
#define EMPTY 0

#ifndef FN_RD
#define FN_RD 0
#endif

#ifndef FN_LOC
#define FN_LOC 0
#endif

typedef struct node_t
{
  unsigned num;
  char str[32];
  int freq;
  int alpha;
} node_t;

typedef int (*fn_read_t) (node_t *);
typedef int (*fn_probe_t) (unsigned);

int read_number (node_t *);
int read_string (node_t *);
int insert (node_t *, int *, fn_probe_t);
int find_loc_linear_probing (unsigned);
int find_loc_quadratic_probing (unsigned);
int find_loc_double_hashing (unsigned);
void dump (void);

node_t hash_table[N + 1];

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
  int i = 0;
  node_t node = { 0 };

  memset (hash_table, EMPTY, sizeof (hash_table));

  while (read_table[FN_RD](&node) != EOF)
    {
      if (insert (&node, &i, *probe_table[FN_LOC]))
        {
          perror ("!panic");
          break;
        }
    }

  dump ();

  return 0;
}

int
read_number (node_t *node)
{
  return scanf ("%d", &node->num);
}

int
read_string (node_t *node)
{
  int h = 1;
  char *p, buf[BUFSIZ];
  int c = scanf ("%s", &buf[0]);
  if (c == 1)
    {
      for (char *s1 = buf; *s1; s1++)
        {
          if (!isalpha (*s1))
            {
              return 0;
            }
        }
      strncpy (node->str, buf, sizeof (node->str));
      for (p = &node->str[0], h = 0; *p; p++)
        {
          h = *p + 31 * h;
        }
    }

  node->num = h;
  return c;
}

int
insert (node_t *node, int *n, fn_probe_t find_loc)
{
  int loc;
  node_t *one;

  loc = find_loc (node->num);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return -1;
    }

  one = &hash_table[loc];
  node->freq = one->freq;

  if (one->num == EMPTY)
    {
      (*n)++;
      if (node->str[0] && isalpha (node->str[0]))
        {
          node->alpha = tolower (node->str[0]) - 'a' + 1;
        }
    }
  node->freq++;

  memcpy (one, node, sizeof (node_t));

  return 0;
}

int
find_loc_linear_probing (unsigned key)
{
  int loc = H (key);
  while (hash_table[loc].num != EMPTY && hash_table[loc].num != key)
    {
      loc = loc % N + 1;
    }
  return loc;
}

int
find_loc_quadratic_probing (unsigned key)
{
  int i = 0;
  int loc = H (key);
  while (hash_table[loc].num != EMPTY && hash_table[loc].num != key)
    {
      i++;
      loc = loc + 2 * i + 3 * i * i;
      if (loc > N)
        {
          loc %= N;
        }
    }
  return loc;
}

int
find_loc_double_hashing (unsigned key)
{
  int loc = H (key);
  int loc1 = H2 (key);
  while (hash_table[loc].num != EMPTY && hash_table[loc].num != key)
    {
      loc += loc1;
      if (loc > N)
        {
          loc %= N;
        }
    }
  return loc;
}

void
dump (void)
{
  int cnt = 0;
  char *read_name, *probe_name;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);

  for (size_t i = 0; i < total; i++)
    {
      node_t *n = &hash_table[i];
      if (n->num != EMPTY)
        {
          cnt++;
          printf ("%4zu %10u %4d %4d %s\n", i, n->num, n->freq, n->alpha,
                  n->str);
        }
    }

  if (read_table[FN_RD] == read_number)
    {
      read_name = "number";
    }
  else if (read_table[FN_RD] == read_string)
    {
      read_name = "string";
    }
  else
    {
      read_name = "X";
    }
  if (probe_table[FN_LOC] == find_loc_linear_probing)
    {
      probe_name = "liner probing";
    }
  else if (probe_table[FN_LOC] == find_loc_quadratic_probing)
    {
      probe_name = "quadratic probing";
    }
  else if (probe_table[FN_LOC] == find_loc_double_hashing)
    {
      probe_name = "double hashing";
    }
  else
    {
      probe_name = "X";
    }

  printf ("------------\ntable %d/(%d,%zu), %s, %s\n", cnt, M, total,
          read_name, probe_name);
}
