#include "../_lang_.h"

typedef char *(*strdup_fn) (const char *s);
typedef char *(*strndup_fn) (const char *s, size_t n);

static char *self_strdup (const char *s);
static char *self_strndup (const char *s, size_t n);

static void test_strdup (strdup_fn fn, const char *s);
static void test_strndup (strndup_fn fn, const char *s);

int
main (int argc, char **argv)
{
  const char *s = 0;

  if (argc < 2)
    {
      fprintf (stderr, "usage: <source-string>\n");
      return 0;
    }

  s = argv[1];

#if (NM_HAVE_STRDUP)
  test_strdup (strdup, s);

#endif /* NM_HAVE_STRDUP */

  test_strdup (self_strdup, s);

#if (NM_HAVE_STRNDUP)
  test_strndup (strndup, s);

#endif /* NM_HAVE_STRNDUP */

  test_strndup (self_strndup, s);

  return 0;
}

char *
self_strdup (const char *s)
{
  char *s1;
  size_t len;

  len = strlen (s);
  if ((s1 = malloc (len + 1)) == NULL)
    return NULL;

  memcpy (s1, s, len);
  return s1;
}

char *
self_strndup (const char *s, size_t n)
{
  char *s1;
  size_t len;

  for (len = 0; len < n && s[len]; len++)
    continue;

  if ((s1 = malloc (len + 1)) == NULL)
    return NULL;

  memcpy (s1, s, len);
  s1[len] = '\0';
  return s1;
}

void
test_strdup (strdup_fn fn, const char *s)
{
  char *s1;
  if ((s1 = fn (s)) == NULL)
    {
      perror (NULL);
      return;
    }
  printf ("dup: %s\n", s1);
  free (s1);
}

void
test_strndup (strndup_fn fn, const char *s)
{
  char *eq, *gt, *lt;
  size_t n;

  n = strlen (s);

  if ((eq = fn (s, n)) == NULL)
    {
      perror (NULL);
      return;
    }
  assert (memcmp (s, eq, n) == 0);
  printf ("ndup: %s\n", eq);
  free (eq);

  if ((lt = fn (s, n - 1)) == NULL)
    {
      perror (NULL);
      return;
    }
  assert (memcmp (s, lt, n - 1) == 0);
  printf ("ndup: %s\n", lt);
  free (lt);

  if ((gt = fn (s, n + 1)) == NULL)
    {
      perror (NULL);
      return;
    }
  assert (memcmp (s, gt, n + 1) == 0);
  printf ("ndup: %s\n", gt);
  free (gt);
}
