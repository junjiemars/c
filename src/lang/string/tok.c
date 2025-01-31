#include "../_lang_.h"

char *self_strtok (char *restrict, char const *restrict);
char *self_strtok_r (char *restrict, char const *restrict, char **restrict);

typedef char *(*strtok_fn) (char *restrict, char const *restrict);
typedef char *(*strtok_r_fn) (char *restrict, char const *restrict,
                              char **restrict);

static void test_strtok (strtok_fn);
static void test_strtok_r (strtok_r_fn);

int
main (void)
{
  test_strtok (self_strtok);
  test_strtok (strtok);
  test_strtok_r (self_strtok_r);

#if (NM_HAVE_STRTOK_R)
  test_strtok_r (strtok_r);
#endif

  return 0;
}

char *
self_strtok_r (char *restrict s, char const *restrict sep, char **last)
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
self_strtok (char *restrict ss, char const *restrict sep)
{
  static char *last;
  return self_strtok_r (ss, sep, &last);
}

void
test_strtok (strtok_fn fn)
{
  char s[128], d[32];
  char *tok;

  strcpy (s, ",,,a,bb,,ccc,,");
  strcpy (d, ",");

  printf ("(%s) (%s)\n------------\n", s, d);
  tok = fn (s, d);
  while (tok)
    {
      printf ("|%s|\n", tok);
      tok = fn (0, d);
    }
}

void
test_strtok_r (strtok_r_fn fn)
{
#if (NM_HAVE_STRTOK_R)
  char s1[64], s2[64];
  char *d = ",/\\;";
  char *tok1, *last1, *tok2, *last2;

  strcpy (s1, "a,bb/ccc\\ddd");
  printf ("(%s) (%s)\n------------\n", s1, d);

  for (tok1 = fn (s1, d, &last1); tok1; tok1 = fn (NULL, d, &last1))
    {
      strcpy (s2, "1;22;333;;;");

      for (tok2 = fn (s2, d, &last2); tok2; tok2 = fn (NULL, d, &last2))
        {
          printf ("|%s:%s|\n", tok1, tok2);
        }
    }
#endif /* strtok_r */
}
