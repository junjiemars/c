#include "../_lang_.h"

size_t self_strspn (const char *s, const char *d);
size_t self_strcspn (const char *s, const char *d);

typedef size_t (*strspn_fn) (const char *, const char *);

static void test_strspn (strspn_fn);

int
main (void)
{
	test_strspn (self_strspn);
	test_strspn (strspn);
  return 0;
}

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
test_strspn (strspn_fn fn)
{
	size_t p;
	char *cs = "the quick brown fox jumps over the lazy dog";
	p = fn (",,,", cs);
	assert (p == 0);
	p = fn ("fox", cs);
	assert (p == 3);
	p = fn ("quick", cs);
	assert (p == 5);
}
