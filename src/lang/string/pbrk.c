#include "../_lang_.h"

char *self_strpbrk (const char *, const char *);

typedef char *(*strpbrk_fn) (const char *, const char *);

static void test_strpbrk (strpbrk_fn);

int
main (void)
{
  test_strpbrk (self_strpbrk);
  test_strpbrk (strpbrk);

  return 0;
}

char *
self_strpbrk (const char *s, const char *d)
{
  const char *p;
  for (; p = d, *s; s++)
    {
      for (; *p; p++)
        {
          if (*s == *p)
            {
              return (char *)s;
            }
        }
    }
  return 0;
}

void
test_strpbrk (strpbrk_fn fn)
{
	char *p;
	p = fn ("a", "abc");
	assert (*p == 'a');
}
