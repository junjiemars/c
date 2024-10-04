#include "_ds_.h"
#include <stdlib.h>
#include <assert.h>

#define N_PRE (sizeof (int64_t))
#define N_POS N_PRE
#define N_IN (N_PRE + N_POS)

typedef struct umbra_str_s
{
  int64_t pre;
  union
  {
    int64_t pos;
    char *ptr;
  };
  size_t len;
} umbra_str_t;

umbra_str_t *new_umbra_str (const char *);
void free_umbra_str (const umbra_str_t *);
int umbra_str_cmp_pre (const umbra_str_t *, const umbra_str_t *);
int umbra_str_cmp_str (const umbra_str_t *, const umbra_str_t *);
int test_cmp_pre (const char *, const char *);
int test_cmp_str (const char *, const char *);

int
main (void)
{
  int cmp;

  cmp = test_cmp_str ("Hello, Nore", "Hello, Nore");
  assert (cmp == 0);

  cmp = test_cmp_str ("Hello, Nore", "Hello, Norf");
  assert (cmp < 0);

  cmp = test_cmp_str ("Hello, Nore", "Hello, Nord");
  assert (cmp > 0);

  cmp = test_cmp_str ("Hello, Nore aaaa", "Hello, Nore");
  assert (cmp > 0);

  cmp = test_cmp_str ("Hello, Nore aaaa", "Hello, Nore aab");
  assert (cmp < 0);

  cmp = test_cmp_pre ("Hello, Nore", "Hello, Nore");
  assert (cmp == 0);

  return 0;
}

umbra_str_t *
new_umbra_str (const char *ss)
{
  umbra_str_t *u;

  u = calloc (1, sizeof (umbra_str_t));
  assert (u != NULL);

  u->len = strlen (ss);
  if (u->len < N_IN)
    {
      memcpy ((char *)&u->pre, ss, u->len);
    }
  else
    {
      strncpy ((char *)&u->pre, ss, N_PRE - 1);
      u->ptr = malloc (u->len);
      assert (u->ptr != NULL);
      strncpy (u->ptr, ss, u->len);
    }
  return u;
}

void
free_umbra_str (const umbra_str_t *u)
{
  if (u->len >= N_IN)
    {
      free (u->ptr);
    }
  free ((void *)u);
}

int
umbra_str_cmp_pre (const umbra_str_t *u1, const umbra_str_t *u2)
{
  return (int)(u1->pre - u2->pre);
}

int
umbra_str_cmp_str (const umbra_str_t *u1, const umbra_str_t *u2)
{
  int max = _max_ (u1->len, u2->len);
  if (u1->len < N_IN && u2->len < N_IN)
    {
      return strncmp ((char *)&u1->pre, (char *)&u2->pre, N_IN);
    }
  else if (u1->len >= N_IN && u2->len >= N_IN)
    {
      return strncmp (u1->ptr, u2->ptr, max);
    }
  else if (u1->len < N_IN && u2->len >= N_IN)
    {
      return strncmp ((char *)&u1->pre, u2->ptr, max);
    }
  else
    {
      return strncmp (u1->ptr, (char *)&u2->pre, max);
    }
}

int
test_cmp_pre (const char *s1, const char *s2)
{
  int d;
  umbra_str_t *u1, *u2;

  u1 = new_umbra_str (s1);
  u2 = new_umbra_str (s2);
  d = umbra_str_cmp_str (u1, u2);
  free_umbra_str (u1);
  free_umbra_str (u2);

  return d;
}

int
test_cmp_str (const char *s1, const char *s2)
{
  int d;
  umbra_str_t *u1, *u2;

  u1 = new_umbra_str (s1);
  u2 = new_umbra_str (s2);
  d = umbra_str_cmp_str (u1, u2);
  free_umbra_str (u1);
  free_umbra_str (u2);

  return d;
}
