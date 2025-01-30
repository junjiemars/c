#include "../_lang_.h"

char *self_strcat (char *restrict, char const *restrict);
char *self_strncat (char *restrict, char const *restrict, size_t);

typedef char *(*strcat_fn) (char *, char const *);
typedef char *(*strncat_fn) (char *, char const *, size_t);

static void test_strcat (strcat_fn);
static void test_strncat (strncat_fn);

int
main (void)
{
  test_strcat (self_strcat);
  test_strcat (strcat);

  test_strncat (self_strncat);

#if (NM_HAVE_STRNCAT)
  test_strncat (strncat);
#endif

  return 0;
}

char *
self_strcat (char *restrict s1, char const *restrict s2)
{
  size_t len1 = strlen (s1);
  size_t len2 = strlen (s2);
  memcpy (s1 + len1, s2, len2 + 1);
  return s1;
}

char *
self_strncat (char *restrict s1, char const *restrict s2, size_t n)
{
  size_t len1 = strlen (s1);
  size_t len2 = strlen (s2);
	if (n < len2)
		{
			len2 = n;
		}
  memcpy (s1 + len1, s2, len2 + 1);
  return s1;
}

void
test_strcat (strcat_fn fn)
{
  char *s1 = malloc (16);

  s1 = fn (s1, "");
  assert (*s1 == '\0');

  s1 = fn (s1, "abc");
  assert (memcmp (s1, "abc", 3) == 0);

  s1 = fn (s1, "def");
  assert (memcmp (s1, "abcdef", 6) == 0);
}


void
test_strncat (strncat_fn fn)
{
  char *s1 = malloc (16);

  s1 = fn (s1, "", 0);
  assert (*s1 == '\0');

  s1 = fn (s1, "abc", 10);
  assert (memcmp (s1, "abc", 3) == 0);

  s1 = fn (s1, "def", 2);
  assert (memcmp (s1, "abcde", 5) == 0);
}
