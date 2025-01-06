#include "../_lang_.h"
#include <stdio.h>
#include <string.h>

typedef size_t (*strspn_fn) (const char *s, const char *d);

size_t self_strspn (const char *s, const char *d);
size_t self_strcspn (const char *s, const char *d);

static void test_strspn (strspn_fn fn, const char *s, const char *d);

size_t
self_strspn (const char *s, const char *d)
{
  size_t n;
  const char *s1;
  const char *p, *p1;

  for (p = d; *p; p++)
    {
      n = 0;
      s1 = s;
      for (p1 = p; *p1 && *s1 && (*p1 == *s1); p1++, s1++)
        {
          n++;
        }
      if (n > 0)
        {
          return n;
        }
    }
  return 0;
}

size_t
self_strcspn (const char *s, const char *d)
{
  const char *p, *s1;
  for (s1 = s; p = d, *s1; s1++)
    {
      for (; *p; p++)
        {
          if (*p == *s1)
            {
              return s1 - s;
            }
        }
    }
  return 0;
}

void
test_strspn (strspn_fn fn, const char *s, const char *d)
{
  size_t s1 = fn (s, d);
  fprintf (stdout, "%zu\n", s1);
}

int
main (int argc, char **argv)
{
  if (argc < 3)
    {
      printf ("where the source string and spn?\n");
      return 0;
    }

  const char *ss = argv[1];
  const char *d = argv[2];
  test_strspn (strspn, ss, d);
  test_strspn (strcspn, ss, d);

  test_strspn (self_strspn, ss, d);
  test_strspn (self_strcspn, ss, d);

  return 0;
}
