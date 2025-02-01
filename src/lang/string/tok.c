#include "../_lang_.h"

char *self_strtok (char *restrict, char const *restrict);
char *self_strtok1 (char *restrict, char const *restrict);
char *self_strtok_r (char *restrict, char const *restrict, char **restrict);
char *self_strtok_r1 (char *restrict, char const *restrict, char **restrict);

typedef char *(*strtok_fn) (char *restrict, char const *restrict);
typedef char *(*strtok_r_fn) (char *restrict, char const *restrict,
                              char **restrict);

static void test_strtok (strtok_fn);
static void test_strtok_r (strtok_r_fn);

int
main (void)
{
  test_strtok (self_strtok);
  test_strtok (self_strtok1);
  test_strtok (strtok);

  test_strtok_r (self_strtok_r);
  test_strtok_r (self_strtok_r1);

#if (NM_HAVE_STRTOK_R)
  test_strtok_r (strtok_r);
#endif /* strtok_r */

  return 0;
}

char *
self_strtok_r1 (char *restrict s, char const *restrict sep, char **last)
{
  int c, sc;
  char *psep, *tok;

  if (s == NULL && (s = *last) == NULL)
    {
      return (NULL);
    }

skip_leading_sep:
  c = *s++;
  for (psep = (char *)sep; (sc = *psep++) != 0;)
    {
      if (c == sc)
        {
          goto skip_leading_sep;
        }
    }

  if (c == 0)
    {
      *last = NULL;
      return (NULL);
    }
  tok = s - 1;

  for (;;)
    {
      c = *s++;
      psep = (char *)sep;
      do
        {
          if (c == (sc = *psep++))
            {
              if (c == 0)
                {
                  s = NULL;
                }
              else
                {
                  s[-1] = '\0';
                }
              *last = s;
              return (tok);
            }
        }
      while (sc != 0);
    }
}

char *
self_strtok_r (char *restrict s, char const *restrict sep, char **last)
{
  if (s == NULL)
    {
      s = *last;
    }

  /* skip leading sep */
  while (*s && strchr (sep, *s))
    {
      ++s;
    }

  if (*s)
    {
      char *start = s;
      *last = start + 1;

      while (**last && !strchr (sep, **last))
        {
          ++*last;
        }

      if (**last)
        {
          **last = '\0';
          ++*last;
        }

      return start;
    }

  return NULL;
}

char *
self_strtok (char *restrict ss, char const *restrict sep)
{
  static char *last;
  return self_strtok_r (ss, sep, &last);
}

char *
self_strtok1 (char *restrict ss, char const *restrict sep)
{
  static char *last;
  return self_strtok_r1 (ss, sep, &last);
}

void
test_strtok (strtok_fn fn)
{
  char s[64], *tok;
  char *d = ",";

  strcpy (s, ",,,a,bb,,ccc,,");

  printf ("\"%s\" \"%s\"\n------------\n", s, d);
  for (tok = fn (s, d); tok; tok = fn (NULL, d))
    {
      printf ("|%s|\n", tok);
    }
}

void
test_strtok_r (strtok_r_fn fn)
{
  char s1[64], s2[64];
  char *d = ",/\\;";
  char *tok1, *last1, *tok2, *last2;

  strcpy (s1, "a,bb/ccc\\ddd");
  printf ("\"%s\" \"%s\"\n------------\n", s1, d);

  for (tok1 = fn (s1, d, &last1); tok1; tok1 = fn (NULL, d, &last1))
    {
      strcpy (s2, "1;22;333;;;");

      for (tok2 = fn (s2, d, &last2); tok2; tok2 = fn (NULL, d, &last2))
        {
          printf ("|%s:%s|\n", tok1, tok2);
        }
    }
}
