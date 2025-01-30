#include "../_lang_.h"

int self_strcmp (char const *, char const *);
int self_strncmp (char const *, char const *, size_t);

typedef int (*strcmp_fn) (char const *, char const *);
typedef int (*strncmp_fn) (char const *, char const *, size_t);

static void test_strcmp (strcmp_fn);
static void test_strncmp (strncmp_fn);

int
main (void)
{
  test_strcmp (self_strcmp);
  test_strncmp (self_strncmp);

#if (NM_HAVE_STRNCMP)
  test_strncmp (strncmp);
#endif

  return 0;
}

int
self_strcmp (char const *s1, char const *s2)
{
  unsigned int a, b;

  do
    {
      a = *s1++;
      b = *s2++;
      if (a != b)
        {
          return a - b;
        }
    }
  while (a != '\0');

  return 0;
}

int
self_strncmp (char const *s1, char const *s2, size_t n)
{
  unsigned int a, b;

  while (n)
    {
      a = *s1++;
      b = *s2++;
      if (a != b)
        {
          return a - b;
        }
      if (a == '\0')
        {
          return 0;
        }
      n--;
    }
  return 0;
}

void
test_strcmp (strcmp_fn fn)
{
  assert (fn ("", "") == 0);
  assert (fn ("abc", "abc") == 0);
  assert (fn ("abc", "abcd") < 0);
  assert (fn ("abcd", "abc") > 0);
}

void
test_strncmp (strncmp_fn fn)
{
  assert (fn ("", "", 10) == 0);
  assert (fn ("abc", "abc", 10) == 0);
  assert (fn ("abc", "abcd", 10) < 0);
  assert (fn ("abcd", "abc", 10) > 0);
  assert (fn ("abcd", "abc", 3) == 0);
  assert (fn ("abc", "abcd", 3) == 0);
}
