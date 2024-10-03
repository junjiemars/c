#include "_ds_.h"
#include <stdlib.h>

#define N_PRE 4
#define N_BUF 8
#define N_IN 12

typedef struct umbra_str_s
{
  int32_t pre;
  union
  {
    int64_t buf;
    char *ptr;
  };
  size_t len;
} umbra_str_t;

umbra_str_t *new_umbra_str (const char *);
void free_umbra_str (const umbra_str_t *);
int umbra_str_cmp (const umbra_str_t *, const umbra_str_t *);
int test_cmp (const char *, const char *);

int
main (void)
{
  int cmp;

  /* cmp = test_cmp ("Hello, Nore", "Hello, Nore"); */
  /* assert (cmp == 0); */

  /* cmp = test_cmp ("Hello, Nore", "Hello, Norf"); */
  /* assert (cmp < 0); */

  /* cmp = test_cmp ("Hello, Nore", "Hello, Nord"); */
  /* assert (cmp > 0); */

  cmp = test_cmp ("Hello, Nore aaaa", "Hello, Nore");
  assert (cmp > 0);

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
      memcpy ((char *)&u->pre, ss, N_PRE);
      u->ptr = malloc (u->len - N_PRE + 1);
      assert (u->ptr != NULL);
      strncpy (u->ptr, ss, u->len - N_PRE);
    }
  return u;
}

void
free_umbra_str (const umbra_str_t *u)
{
  if (u->len >= n_in)
    {
      free (u->ptr);
    }
  free ((void *)u);
}

int
umbra_str_cmp (const umbra_str_t *u1, const umbra_str_t *u2)
{
  int d;
  if (u1->len >= N_IN && u2->len >= N_IN)
    {
      d = u1->pre - u2->pre;
      if (d == 0)
        {
          return strncmp (u1->ptr, u2->ptr, _max_ (u1->len, u2->len) - N_PRE);
        }
      return d;
    }
  else if (u1->len < N_IN && u2->len >= N_IN)
    {
      d = strncmp ((char *)&u1->pre, u2->pre
    }
  return d;
}

int
test_cmp (const char *s1, const char *s2)
{
  int d;
  umbra_str_t *u1, *u2;

  u1 = new_umbra_str (s1);
  u2 = new_umbra_str (s2);
  d = umbra_str_cmp (u1, u2);
  free_umbra_str (u1);
  free_umbra_str (u2);

  return d;
}
