#include "../_algo_.h"
#include <errno.h>

#define M 20
#define N 23

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
  int num;
  char str[32];
} node_t;

typedef int (*fn_read_t) (node_t *);
typedef int (*fn_probe_t) (int);

int read_number (node_t *);
int read_string (node_t *);
int insert (node_t *, int *, fn_probe_t);
int find_loc_linear_probing (int);
int find_loc_quadratic_probing (int);
int find_loc_double_hashing (int);
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
  node_t node;
  int i = 0;

  memset (hash_table, EMPTY, sizeof (hash_table));

  while (read_table[FN_RD](&node) == 1)
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
  int h = 0;
  char *p;
  int c = scanf ("%s", &node->str[0]);
  if (c == 1)
    {
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

  loc = find_loc (node->num);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return -1;
    }

  if (hash_table[loc].num == EMPTY)
    {
      (*n)++;
    }

  memcpy (&hash_table[loc], node, sizeof (node_t));

  return 0;
}

int
find_loc_linear_probing (int key)
{
  int loc = H (key);
  while (hash_table[loc].num != EMPTY && hash_table[loc].num != key)
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
find_loc_double_hashing (int key)
{
  int loc = H (key);
  int loc1 = H2 (key);
  while (hash_table[loc].num != EMPTY && hash_table[loc].num != key)
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
  char *read_name, *probe_name;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);

  for (size_t i = 0; i < total; i++)
    {
      node_t *n = &hash_table[i];
      if (n->num != EMPTY)
        {
          cnt++;
          printf ("%4zu %8d %s\n", i, n->num, n->str);
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
