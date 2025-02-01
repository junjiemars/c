#include "../_ds_.h"
#include <assert.h>
#include <stdlib.h>

#if (NM_CPU_LITTLE_ENDIAN)
#include <arpa/inet.h>
#define _hton32_(x) (htonl ((x)))
#define _hton64_(x)                                                           \
  ((uint64_t)htonl ((x)&0xffffffff) << 32 | htonl ((x) >> 32))
#else
#define _hton32_(x) (x)
#define _hton64_(x) (x)
#endif

/**
 * Umbra string
 * https://cedardb.com/blog/german_strings/
 * https://db.in.tum.de/~freitag/papers/p29-neumann-cidr20.pdf
 */

typedef struct Umbra
{
#if (NM_CPU_LITTLE_ENDIAN)
  uint32_t len;
  uint32_t s1;
  union
  {
    uint64_t s2;
    char const *ptr;
  };
#else
  union
  {
    uint64_t s2;
    char const *ptr;
  };
  uint32_t s1;
  uint32_t len;
#endif
} Umbra;

Umbra from_cstr (char const *);
char *to_cstr (Umbra const *);
Umbra *new_umbra (size_t);
size_t umbra_strlen (Umbra const *);
int umbra_strcmp (Umbra const *, Umbra const *);
Umbra *umbra_strcpy (Umbra *, Umbra const *);
Umbra *umbra_strcat (Umbra *restrict, Umbra const *restrict);

static void test_cstr (void);
static void test_strlen (void);
static void test_strcmp (void);
static void test_strcpy (void);
static void test_strcat (void);

int
main (void)
{
  test_cstr ();
  test_strlen ();
  test_strcmp ();
  test_strcpy ();
  test_strcat ();

  return 0;
}

Umbra
from_cstr (char const *s)
{
  Umbra us1 = { 0 };
  char *ps1 = ((char *)&us1) + offsetof (Umbra, s1);
  size_t size12 = sizeof (us1.s1) + sizeof (us1.s2);

  us1.len = (uint32_t)strlen (s);
  if (us1.len > 0)
    {
      strncpy (ps1, s, size12);

      if (us1.len >= size12)
        {
          us1.ptr = s;
        }
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

Umbra *
new_umbra (size_t count)
{
  return calloc (count, sizeof (Umbra));
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
  size_t size12 = sizeof (s1->s1) + sizeof (s1->s2);

  n = (int)(_hton32_ (s1->s1) - _hton32_ (s2->s1));
  if (n)
    {
      return n;
    }

  if (s1->len < size12 && s2->len < size12)
    {
      return (int)(_hton64_ (s1->s2) - _hton64_ (s2->s2));
    }

  if (s1->len < size12)
    {
      return strcmp ((char *)&s1->s2, s2->ptr + sizeof (s2->s1));
    }

  if (s2->len < size12)
    {
      return strcmp (s1->ptr + sizeof (s1->s1), (char *)&s2->s1);
    }

  return strcmp (s1->ptr + sizeof (s1->s1), s2->ptr + sizeof (s2->s1));
}

Umbra *
umbra_strcpy (Umbra *dst, Umbra const *src)
{
  *dst = *src;
  return dst;
}

Umbra *
umbra_strcat (Umbra *restrict s1, Umbra const *restrict s2)
{
  char *ss;
  size_t size = s1->len + s2->len;

  if (size == 0)
    {
      return s1;
    }

  if (size >= sizeof (s1->s1) + sizeof (s1->s2))
    {
      if ((ss = malloc (size + 1)) == NULL)
        {
          return NULL;
        }
      memcpy (ss, (char *)&s1->s1, s1->len + 1);
      memcpy (ss + s1->len, (char *)&s2->s1, s2->len + 1);
      *s1 = from_cstr (ss);
    }
  else
    {
      memcpy ((char *)&s1->s1 + s1->len, (char *)&s2->s1, s2->len + 1);
      s1->len = (uint32_t)size;
    }

  return s1;
}

void
test_cstr (void)
{
  Umbra u1;
  char *s1;

  s1 = "";
  u1 = from_cstr (s1);
  assert (memcmp (s1, to_cstr (&u1), strlen (s1)) == 0);

  s1 = "12345678901";
  u1 = from_cstr (s1);
  assert (memcmp (s1, to_cstr (&u1), strlen (s1)) == 0);

  s1 = "123456789012";
  u1 = from_cstr (s1);
  assert (memcmp (s1, to_cstr (&u1), strlen (s1)) == 0);
}

void
test_strlen (void)
{
  Umbra u1;
  char *s1;

  s1 = "";
  u1 = from_cstr (s1);
  assert (umbra_strlen (&u1) == strlen (s1));

  s1 = "12345678901";
  u1 = from_cstr (s1);
  assert (umbra_strlen (&u1) == strlen (s1));

  s1 = "123456789012";
  u1 = from_cstr (s1);
  assert (umbra_strlen (&u1) == strlen (s1));
}

void
test_strcmp (void)
{
  Umbra u1, u2;

  u1 = from_cstr ("");
  u2 = from_cstr ("");
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("1234");
  u2 = from_cstr ("1234");
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("1234");
  u2 = from_cstr ("4321");
  assert (umbra_strcmp (&u1, &u2) < 0);

  u1 = from_cstr ("12345678901");
  u2 = from_cstr ("12345678901");
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("12345678901");
  u2 = from_cstr ("12341098765 ");
  assert (umbra_strcmp (&u1, &u2) > 0);

  u1 = from_cstr ("12345678901");
  u2 = from_cstr ("123456789012");
  assert (umbra_strcmp (&u1, &u2) < 0);
  assert (umbra_strcmp (&u2, &u1) > 0);

  u1 = from_cstr ("123456789012");
  u2 = from_cstr ("123456789012");
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("12356");
  u2 = from_cstr ("12345678901");
  assert (umbra_strcmp (&u1, &u2) > 0);
  assert (umbra_strcmp (&u2, &u1) < 0);

  u1 = from_cstr ("123356789012");
  u2 = from_cstr ("123456789012");
  assert (umbra_strcmp (&u1, &u2) < 0);
  assert (umbra_strcmp (&u2, &u1) > 0);

  u1 = from_cstr ("123456789012");
  u2 = from_cstr ("123456789013");
  assert (umbra_strcmp (&u1, &u2) < 0);
  assert (umbra_strcmp (&u2, &u1) > 0);

  u1 = from_cstr ("123456789012");
  u2 = from_cstr ("1234567890123");
  assert (umbra_strcmp (&u1, &u2) < 0);
  assert (umbra_strcmp (&u2, &u1) > 0);
}

void
test_strcpy (void)
{
  Umbra u1, u2;
  u1 = from_cstr ("");
  (void)umbra_strcpy (&u2, &u1);
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("12345678901");
  (void)umbra_strcpy (&u2, &u1);
  assert (umbra_strcmp (&u1, &u2) == 0);

  u1 = from_cstr ("123456789012");
  (void)umbra_strcpy (&u2, &u1);
  assert (umbra_strcmp (&u1, &u2) == 0);
}

void
test_strcat (void)
{
  Umbra u1, u2, u3;
  size_t size;

  u1 = from_cstr ("");
  u2 = from_cstr ("");
  assert (umbra_strcat (&u1, &u2) != NULL);
  assert (umbra_strlen (&u1) == 0);

  u1 = from_cstr ("1234");
  u2 = from_cstr ("5678901");
  u3 = from_cstr ("12345678901");
  size = u1.len + u2.len;
  assert (umbra_strcat (&u1, &u2) != NULL);
  assert (umbra_strlen (&u1) == size);
  assert (umbra_strcmp (&u1, &u3) == 0);

  u1 = from_cstr ("12345678901");
  u2 = from_cstr ("12345678901");
  u3 = from_cstr ("1234567890112345678901");
  size = u1.len + u2.len;
  assert (umbra_strcat (&u1, &u2) != NULL);
  assert (umbra_strlen (&u1) == size);
  assert (umbra_strcmp (&u1, &u3) == 0);
  if (u1.ptr)
    {
      free ((void *)u1.ptr);
    }
}
