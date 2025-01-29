#include "../_lang_.h"

typedef char *(*strcat_fn) (char *s1, const char *s2);

static char *self_strcat (char *restrict, char const *restrict);
static void test_strcat (strcat_fn, char *, char const *);

int
main (int argc, char **argv)
{
  char *s1, *s2;
  char *arg1, *arg2;
  size_t len1, len2;

  if (argc < 3)
    {
      fprintf (stderr, "usage: <s1> <s2>\n");
      return 0;
    }
  arg1 = argv[1];
  arg2 = argv[2];

  len1 = strlen (arg1);
  len2 = strlen (arg2);

  if ((s1 = malloc (len1 + len2 + 1)) == NULL)
    {
      perror (NULL);
      goto clean_exit;
    }
  if ((s2 = malloc (len2 + 1)) == NULL)
    {
      perror (NULL);
      goto clean_exit;
    }

  strcpy (s1, arg1);
  strcpy (s2, arg2);
  test_strcat (strcat, s1, s2);

  strcpy (s1, arg1);
  strcpy (s2, arg2);
  test_strcat (self_strcat, s1, s2);

clean_exit:
  free (s1);
  free (s2);

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

void
test_strcat (strcat_fn fn, char *s1, const char *s2)
{
  char *ss;
  ss = fn (s1, s2);
  fprintf (stdout, "%s\n", ss);
}
