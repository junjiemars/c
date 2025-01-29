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
  uint32_t len;
  uint32_t s1;
  union
  {
    uint64_t s2;
    char const *ptr;
  };
} Umbra;

Umbra from_cstr (char const *);
char *to_cstr (Umbra const *);
size_t umbra_strlen (Umbra const *);
int umbra_strcmp (Umbra const *, Umbra const *);
Umbra *umbra_strcpy (Umbra *, Umbra const *);

int
main (void)
{
  char *s1 = "Hello";
  char *s2 = "Hello, Nore!";
  Umbra u1, u2, *u3;

  u1 = from_cstr (s1);
  assert (umbra_strlen (&u1) == strlen (s1));
  assert (strcmp (s1, to_cstr (&u1)) == 0);

  u2 = from_cstr (s2);
  assert (umbra_strcmp (&u1, &u1) == 0);
  assert (umbra_strcmp (&u1, &u2) < 0);
  assert (umbra_strcmp (&u2, &u1) > 0);
  assert (strcmp (s2, to_cstr (&u2)) == 0);

  u1 = from_cstr ("hello, Nore!");
  assert (umbra_strcmp (&u1, &u2) > 0);
  assert (umbra_strcmp (&u2, &u1) < 0);

  u3 = malloc (sizeof (Umbra));
  (void)umbra_strcpy (u3, &u2);
  assert (umbra_strcmp (&u2, u3) == 0);

  return 0;
}

Umbra
from_cstr (char const *s)
{
  Umbra us1 = { 0 };
  char *ps1 = ((char *)&us1) + offsetof (Umbra, s1);

  us1.len = strlen (s);
  strncpy (ps1, s, sizeof (us1.s1) + sizeof (us1.s2) - 1);

  if (us1.len >= sizeof (us1.ptr))
    {
      ((char *)&us1.s1)[sizeof (us1.s1) - 1] = 0;
      us1.ptr = s;
    }

  return us1;
}

char *
to_cstr (Umbra const *u)
{
  if (u->len < sizeof (u->s1) + sizeof (u->s2))
    {
      return (char *)u + offsetof (Umbra, s1);
    }
  return (char *)u->ptr;
}

size_t
umbra_strlen (Umbra const *s)
{
  return s->len;
}

int
umbra_strcmp (Umbra const *s1, Umbra const *s2)
{
  int n;

  if (s1->len < sizeof (s1->ptr) && s2->len < sizeof (s2->ptr))
    {
      return *(uint64_t *)s1 - *(uint64_t *)s2;
    }

  n = memcmp ((char *)&s1->s1, (char *)&s2->s1, sizeof (s1->s1) - 1);
  if (n)
    {
      return n;
    }

  if (s1->len < sizeof (uint64_t))
    {
      return strcmp ((char *)&s1->s1, s2->ptr);
    }

  if (s2->len < sizeof (uint64_t))
    {
      return strcmp (s1->ptr, (char *)&s2->s1);
    }

  return strcmp (s1->ptr, s2->ptr);
}

Umbra *
umbra_strcpy (Umbra *dst, Umbra const *src)
{
  *dst = *src;
  return dst;
}
