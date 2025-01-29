#include "../_lang_.h"

typedef char *(*strchr_fn) (const char *s, int);
typedef char *(*strrchr_fn) (const char *s, int);

static char *self_strchr (const char *s, int);
static char *self_strrchr (const char *s, int);

static void test_strchr (strchr_fn, char *s, int);

int
main (int argc, char **argv)
{
  char *ss;
  int c;

  if (argc < 3)
    {
      fprintf (stderr, "usage: <src> <find>\n");
      return 1;
    }

  ss = argv[1];
  c = argv[2][0];

  test_strchr (strchr, ss, c);
  test_strchr (strrchr, ss, c);

  test_strchr (self_strchr, ss, c);
  test_strchr (self_strrchr, ss, c);

  return 0;
}

void
test_strchr (strchr_fn fn, char *s, int c)
{
  char *s1;

  s1 = fn (s, c);
  if (s1)
    {
      fprintf (stdout, "%s\n", s1);
    }
  else
    {
      fprintf (stdout, "%c: no found\n", c);
    }
}

char *
self_strchr (const char *s, int c)
{
  if (!s)
    {
      return NULL;
    }

  do
    {
      if (*s == c)
        {
          return (char *)s;
        }
    }
  while (*s++);
  return NULL;
}

char *
self_strrchr (const char *s, int c)
{
  char const *pre = NULL;

  if (!s)
    {
      return NULL;
    }

  do
    {
      if (*s == c)
        {
          pre = s;
        }
    }
  while (*s++);
  return (char *)pre;
}
