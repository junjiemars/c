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

#define H(x) ((x) % N + 1)
#define HE(x) (hash_table[(x)])
#define EMPTY 0

#define RD_NUM 0
#define RD_STR 1

#ifndef FN_RD
#define FN_RD RD_NUM
#endif

#ifndef FN_LOC
#define FN_LOC 0
#endif

#define PE(f) (probe_table[(f)])

typedef struct Entry
{
  unsigned num;
  char str[32];
  unsigned freq;
  int alpha;
  int used;
} Entry;

typedef int (*FnRead) (Entry *);
typedef int (*FnProbe) (unsigned);

int insert_entry (Entry *, unsigned *, FnProbe);
int search_entry (unsigned, Entry **);
int delete_entry (unsigned);
int read_number (Entry *);
int read_string (Entry *);
int probe_linear (unsigned);
int probe_quadratic (unsigned);
int probe_double_hashing (unsigned);
unsigned get_relative_prime (unsigned);
unsigned str_to_num (char const *, unsigned);
void dump (void);

Entry hash_table[N + 1];

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
  Entry node = { 0 };

  memset (hash_table, EMPTY, sizeof (hash_table));

  while ((rc = read_table[FN_RD](&node)) != EOF)
    {
      if (rc == 1)
        {
          if (insert_entry (&node, &i, *probe_table[FN_LOC]))
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
read_number (Entry *node)
{
  int rc = scanf ("%u", &node->num);
  if (rc == 0)
    {
      int c;
      for (c = getchar (); c != EOF && !isdigit (c); c = getchar ())
        {
          /* void */
        }
      if (c == EOF)
        {
          return EOF;
        }
      ungetc (c, stdin);
    }
  return rc;
}

int
read_string (Entry *node)
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
      h = str_to_num (node->str, h);
    }

  node->num = h;
  return rc;
}

int
insert_entry (Entry *node, unsigned *n, FnProbe probe)
{
  int loc;
  Entry *one;

  loc = probe (node->num);

  if (*n >= M)
    {
      errno = EOVERFLOW;
      return EOF;
    }

  one = &HE (loc);

  if (!one->used)
    {
      (*n)++;
      one->num = node->num;
      one->used = 1;
#if (FN_RD == RD_STR)
      if (node->str[0] && isalpha (node->str[0]))
        {
          one->alpha = 1 + tolower (node->str[0]) - 'a';
        }
#endif
    }
#if (FN_RD == RD_STR)
  strncpy (one->str, node->str, sizeof (one->str));
#endif
  one->freq++;

  return 0;
}

int
search_entry (unsigned key, Entry **found)
{
  int loc = PE (FN_LOC) (key);
  *found = NULL;
  if (HE (loc).used && HE (loc).num == key)
    {
      *found = &HE (loc);
      return 1;
    }
  return 0;
}

int
delete_entry (unsigned key)
{
  Entry *found;
  if (search_entry (key, &found))
    {
      found->used = EMPTY;
      return 1;
    }
  return 0;
}

int
probe_linear (unsigned key)
{
  static unsigned rp = EMPTY;
  int loc = H (key);

  if (rp == EMPTY)
    {
      rp = get_relative_prime (N);
    }

  while (HE (loc).used && HE (loc).num != key)
    {
      loc = H (loc + rp);
    }

  return loc;
}

int
probe_quadratic (unsigned key)
{
  int i = 0;
  int loc = H (key);
  while (HE (loc).used && HE (loc).num != key)
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
  int loc = H (key);
  int loc2 = H (key + 1);
  while (HE (loc).used && HE (loc).num != key)
    {
      loc += loc2;
      if (loc > N)
        {
          loc -= N;
        }
    }
  return loc;
}

unsigned
get_relative_prime (unsigned n)
{
  for (unsigned x = 3; x < n; x++)
    {
      if ((n / x) * x != n)
        {
          return x;
        }
    }
  return (n - 1);
}

unsigned
str_to_num (char const *ss, unsigned base)
{
  int w = 3;
  for (char const *p = ss; *p; w += 2, p++)
    {
      base += w * (*p);
    }
  return base;
}

void
dump (void)
{
  int cnt = 0;
  char *read_name, *probe_name;
  size_t total = sizeof (hash_table) / sizeof (hash_table[0]);

  for (size_t i = 0; i < total; i++)
    {
      if (hash_table[i].used)
        {
          cnt++;
        }
    }

  if (read_table[FN_RD] == read_number)
    {
      read_name = _str_ (read_numer);
    }
  else if (read_table[FN_RD] == read_string)
    {
      read_name = _str_ (read_string);
    }
  else
    {
      read_name = "X";
    }
  if (probe_table[FN_LOC] == probe_linear)
    {
      probe_name = _str_ (probe_liner);
    }
  else if (probe_table[FN_LOC] == probe_quadratic)
    {
      probe_name = _str_ (probe_quadratic);
    }
  else if (probe_table[FN_LOC] == probe_double_hashing)
    {
      probe_name = _str_ (probe_double_hashing);
    }
  else
    {
      probe_name = "X";
    }

  fprintf (stderr, "table %d/(%d,%zu) %s %s\n------------\n", cnt, M, total,
           read_name, probe_name);
  fprintf (stderr, "%4s %10s %4s %5s %s\n", "idx", "num", "freq", "alpha",
           "str");

  for (size_t i = 0; i < total; i++)
    {
      Entry const *n = &hash_table[i];
      if (n->used)
        {
          printf ("%4zu %10u %4d %5d %s\n", i, n->num, n->freq, n->alpha,
                  n->str);
        }
    }
}
