#include "../_algo_.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>

#if !defined(M) || ((M + 0) < 1)
#define M 20
#endif

#if !defined(N) || ((N + 0) < (M - 3))
#define N (M + 3)
#endif

#define H1(x) ((x) % N + 1)
#define H2(x) (((x) + 1) % N + 1)
#define HE(x) (hash_table[(x)])
#define EMPTY 0

#ifndef FN_RD
#define FN_RD 0
#endif

#ifndef FN_LOC
#define FN_LOC 0
#endif

typedef struct Node
{
  unsigned num;
  char str[32];
  unsigned freq;
  int alpha;
} Node;

typedef int (*FnRead) (Node *);
typedef int (*FnProbe) (unsigned);

int read_number (Node *);
int read_string (Node *);
int insert (Node *, unsigned *, FnProbe);
int probe_linear (unsigned);
int probe_quadratic (unsigned);
int probe_double_hashing (unsigned);
void dump (void);

Node hash_table[N + 1];

FnRead read_table[] = {
  read_number,
  read_string,
  (FnRead)0,
};

FnProbe probe_table[] = {
  probe_linear,
  probe_quadratic,
  probe_double_hashing,
  (FnProbe)0,
};

int
main (void)
{
  int rc;
  unsigned int i = 0;
  Node node = { 0 };

  memset (hash_table, EMPTY, sizeof (hash_table));

  while ((rc = read_table[FN_RD](&node)) != EOF)
    {
      if (rc == 1)
        {
          if (insert (&node, &i, *probe_table[FN_LOC]))
            {
              perror ("!panic");
              break;
            }
        }
    }

  dump ();

  return 0;
}

int
read_number (Node *node)
{
  int rc = scanf ("%u", &node->num);
  if (rc == 0)
    {
      int ch = getchar ();
      while (ch != EOF && !isdigit (ch))
        {
          ch = getchar ();
        }
      if (ch == EOF)
        {
          return EOF;
        }
      ungetc (ch, stdin);
    }
  return rc;
}

int
read_string (Node *node)
{
  int rc;
  int h = 1;
  char buf[BUFSIZ];

  assert (sizeof (node->str) < BUFSIZ && "buf should larger than node->str");

  if ((rc = scanf ("%s", &buf[0])) == 1)
    {
      for (char *s1 = buf; *s1; s1++)
        {
          if (!isalpha (*s1))
            {
              return 0;
            }
        }
      strncpy (node->str, buf, sizeof (node->str));
      for (char *p = node->str; *p; p++)
        {
          h = *p + 31 * h;
        }
    }

  node->num = h;
  return rc;
}

int
insert (Node *node, unsigned *n, FnProbe probe)
{
  int loc;
  Node *one;

  loc = probe (node->num);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return EOF;
    }

  one = &HE (loc);

  if (one->num == EMPTY)
    {
      (*n)++;
      one->num = node->num;
#if FN_RD == 1 /* read_string */
      if (node->str[0] && isalpha (node->str[0]))
        {
          one->alpha = 1 + tolower (node->str[0]) - 'a';
        }
#endif
    }
#if FN_RD == 1
  strncpy (one->str, node->str, sizeof (one->str));
#endif
  one->freq++;

  return 0;
}

int
probe_linear (unsigned key)
{
  int loc = H1 (key);
  while (HE (loc).num != EMPTY && HE (loc).num != key)
    {
      loc = loc % N + 1;
    }
  return loc;
}

int
probe_quadratic (unsigned key)
{
  int i = 0;
  int loc = H1 (key);
  while (HE (loc).num != EMPTY && HE (loc).num != key)
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
probe_double_hashing (unsigned key)
{
  int loc = H1 (key);
  int loc1 = H2 (key);
  while (HE (loc).num != EMPTY && HE (loc).num != key)
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
      Node *n = &hash_table[i];
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
  if (probe_table[FN_LOC] == probe_linear)
    {
      probe_name = "liner probing";
    }
  else if (probe_table[FN_LOC] == probe_quadratic)
    {
      probe_name = "quadratic probing";
    }
  else if (probe_table[FN_LOC] == probe_double_hashing)
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
