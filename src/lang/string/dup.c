#include "../_lang_.h"

typedef char *(*strdup_fn) (const char *s);
typedef char *(*strndup_fn) (const char *s, size_t n);

static char *self_strdup (const char *s);
static char *self_strndup (const char *s, size_t n);

static void test_strdup (strdup_fn fn);
static void test_strndup (strndup_fn fn);

int
main (void)
{
  test_strdup (self_strdup);
  test_strndup (self_strndup);

#if (NM_HAVE_STRDUP)
  test_strdup (strdup);
#endif /* NM_HAVE_STRDUP */

#if (NM_HAVE_STRNDUP)
  test_strndup (strndup);
#endif /* NM_HAVE_STRNDUP */

  return 0;
}

char *
self_strdup (const char *s)
{
  char *s1;
  size_t len;

  len = strlen (s) + 1;
  if ((s1 = malloc (len)) == NULL)
    {
      return NULL;
    }
  memcpy (s1, s, len);

  return s1;
}

char *
self_strndup (const char *s, size_t n)
{
  char *s1;
  size_t len;

  for (len = 0; len < n && s[len]; len++)
    {
      continue;
    }

  if ((s1 = malloc (len + 1)) == NULL)
    {
      return NULL;
    }

  memcpy (s1, s, len);
  s1[len] = '\0';
  return s1;
}

void
test_strdup (strdup_fn fn)
{
  char *s1;
  s1 = fn ("");
  assert (*s1 == '\0');
  free (s1);

	s1 = fn ("abc");
	assert (strcmp (s1, "abc") == 0);
	free (s1);
}

void
test_strndup (strndup_fn fn)
{
  char *s1;

  s1 = fn ("", 0);
	assert (*s1 == '\0');
  free (s1);

	s1 = fn ("", 1);
	assert (*s1 == '\0');
  free (s1);

	s1 = fn ("abc", 2);
	assert (strcmp (s1, "ab") == 0);
	assert (strcmp (s1, "abc") < 0);
	free (s1);

	s1 = fn ("abc", 8);
	assert (strcmp (s1, "abc") == 0);
	free (s1);
}
