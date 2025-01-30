#include "../_lang_.h"

char *self_strchr (const char *s, int);
char *self_strrchr (const char *s, int);

typedef char *(*strchr_fn) (const char *s, int);
typedef char *(*strrchr_fn) (const char *s, int);

static void test_strchr (strchr_fn);
static void test_strrchr (strrchr_fn);

int
main (void)
{
  test_strchr (self_strchr);
  test_strchr (strchr);
  test_strrchr (self_strchr);
  test_strrchr (strrchr);

  return 0;
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

void
test_strchr (strchr_fn fn)
{
	char *p;
	p = fn ("", 'a');
	assert (p == NULL);
	p = fn ("abc", 'a');
	assert (*p == 'a');
	p = fn ("abc", '\0');
	assert (*p == '\0');
}

void
test_strrchr (strrchr_fn fn)
{
	char *p;
	p = fn ("", 'a');
	assert (p == NULL);
	p = fn ("abc", 'a');
	assert (*p == 'a');
	p = fn ("abc", '\0');
	assert (*p == '\0');
}
