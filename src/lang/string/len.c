#include "../_lang_.h"

size_t self_strlen (char const *);
size_t self_strnlen (char const *, size_t);

typedef size_t (*strlen_fn) (char const *);
typedef size_t (*strnlen_fn) (char const *, size_t);

static void test_strlen (strlen_fn);
static void test_strnlen (strnlen_fn);

int
main (void)
{
  test_strlen (self_strlen);
  test_strlen (strlen);

	test_strnlen (self_strnlen);

#if (NM_HAVE_STRNLEN)
	test_strnlen (strnlen);
#endif
  return 0;
}

size_t
self_strlen (char const *s)
{
  size_t n;
  for (n = 0; *s != '\0'; s++, n++)
    {
      continue;
    }
  return n;
}

size_t
self_strnlen (char const *s, size_t n)
{
	size_t len = 0;
	for (len = 0; len < n && *s; s++, len++)
		{
			continue;
		}
  return len;
}

void
test_strlen (strlen_fn fn)
{
  assert (fn ("") == 0);
  assert (fn ("abc") == 3);
}

void
test_strnlen (strnlen_fn fn)
{
	assert (fn ("", 10) == 0);
	assert (fn ("abc", 10) == 3);
	assert (fn ("abcd", 3) == 3);
}
