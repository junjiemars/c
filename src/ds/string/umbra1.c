#include "../_ds_.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Umbra string
 * https://cedardb.com/blog/german_strings/
 * https://db.in.tum.de/~freitag/papers/p29-neumann-cidr20.pdf
 */

typedef struct Umbra
{
  uint32_t pre;
  union
  {
    uint32_t pos;
    char const *ptr;
  };
  uint32_t len;
} Umbra;

Umbra from_cstr (char const *);
size_t umbra_strlen (Umbra const *);
int umbra_strcmp (Umbra const *, Umbra const *);

int
main (void)
{
  char *s1 = "Hello";
  char *s2 = "Hello, Nore!";
  Umbra u1, u2;

  u1 = from_cstr (s1);
  assert (umbra_strlen (&u1) == strlen (s1));

  u2 = from_cstr (s2);
  assert (umbra_strcmp (&u1, &u1) == 0);
  assert (umbra_strcmp (&u1, &u2) < 0);
	assert (umbra_strcmp (&u2, &u1) > 0);

  return 0;
}

Umbra
from_cstr (char const *s)
{
  Umbra us1 = { 0 };

  us1.len = strlen (s);
  strncpy ((char *)&us1, s, sizeof (uint64_t) - 1);

  if (us1.len >= sizeof (uint64_t))
    {
      us1.ptr = s;
    }

  return us1;
}

size_t
umbra_strlen (Umbra const *s)
{
  return s->len;
}

int
umbra_strcmp (Umbra const *s1, Umbra const *s2)
{
  if (s1->len < sizeof (uint64_t) && s2->len < sizeof (uint64_t))
    {
      return (uint64_t *)s1 - (uint64_t *)s2;
    }

  if (s1->len < sizeof (uint64_t))
    {
      return strcmp ((char *)s1, s2->ptr);
    }

  if (s2->len < sizeof (uint64_t))
    {
      return strcmp (s1->ptr, (char *)s2);
    }

  return strcmp (s1->ptr, s2->ptr);
}
