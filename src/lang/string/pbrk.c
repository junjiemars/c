#include <_lang_.h>
#include <string.h>
#include <stdio.h>

typedef char *(*strpbrk_fn)(const char *ss, const char *d);

char *self_strpbrk(const char *ss, const char *d);

static void test_strpbrk(strpbrk_fn, const char *ss, const char *d);

void
test_strpbrk(strpbrk_fn fn, const char *ss, const char *d)
{
  char *s1 = fn(ss, d);
  if (s1)
    {
      fprintf(stdout, "|%s|\n", s1);
    } else
    {
      fprintf(stdout, "%s: no found\n", d);
    }
}

char *
self_strpbrk(const char *s, const char *d)
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


int
main(__attribute__((unused)) int argc, char **argv)
{

  if (argc < 3)
    {
      printf("where the source string and delim?\n");
      return 0;
    }

  const char *ss = argv[1];
  const char *d = argv[2];
  test_strpbrk(strpbrk, ss, d);
  test_strpbrk(self_strpbrk, ss, d);

  return 0;
}
