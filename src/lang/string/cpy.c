#include "../_lang_.h"

char *self_strcpy (char *, char const *);
char *self_stpcpy (char *, char const *);
char *self_strncpy (char *, char const *, size_t);

typedef char *(*strcpy_fn) (char *, char const *);
typedef char *(*stpcpy_fn) (char *, char const *);
typedef char *(*strncpy_fn) (char *, char const *, size_t);

static void test_strcpy (strcpy_fn);
static void test_stpcpy (stpcpy_fn);
static void test_strncpy (strncpy_fn);

int
main (void)
{
  test_strcpy (self_strcpy);
  test_strcpy (strcpy);
	test_stpcpy (self_stpcpy);
	test_stpcpy (stpcpy);
  test_strncpy (self_strncpy);

#if (NM_HAVE_STRNCPY)
	test_strncpy (strncpy);
#endif

  return 0;
}

char *
self_strcpy (char *dst, char const *src)
{
  char *d = dst;
  while ((*d++ = *src++) != '\0')
    {
      continue;
    }
  return dst;
}

char *
self_stpcpy (char *dst, char const *src)
{
  char *d = dst;
  while ((*d++ = *src++) != '\0')
    {
      continue;
    }
  return d - 1;
}

char *
self_strncpy (char *dst, char const *src, size_t len)
{
  size_t i;
  char *d1 = dst;
  for (i = 0; i < len;)
    {
      if ((*dst++ = *src++) == '\0')
        {
          for (i++; i < len; i++)
            {
              *dst++ = '\0';
            }
        }
      else
        {
          i++;
        }
    }
  return d1;
}

void
test_strcpy (strcpy_fn fn)
{
	char *dst;
	dst = malloc (16);
	assert (dst != NULL);
	dst = fn (dst, "");
	assert (*dst == '\0');
	dst = fn (dst, "abc");
	assert (memcmp (dst, "abc", 3) == 0);
	free (dst);
}

void
test_stpcpy (stpcpy_fn fn)
{
	char *dst, *p;
	dst = malloc (16);
	assert (dst != NULL);
	p = fn (dst, "");
	assert (*p == '\0' && *dst == '\0');
	free (dst);
}

void
test_strncpy (strncpy_fn fn)
{
	char *dst;
	size_t n = 16;
	dst = malloc (n);
	assert (dst != NULL);
	dst = fn (dst, "", 1);
	assert (*dst == '\0');
	dst = fn (dst, "abc", 8);
	assert (memcmp (dst, "abc", 4) == 0);
	dst = fn (dst, "abc", 2);
	assert (memcmp (dst, "abc", 3) == 0);
	free (dst);
}
