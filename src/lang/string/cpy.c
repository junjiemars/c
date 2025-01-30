#include "../_lang_.h"

char *self_strcpy (char *, char const *);
char *self_strpcpy (char *, char const *);
char *self_strncpy (char *, char const *, size_t);

typedef char *(*strcpy_fn) (char *, char const *);
typedef char *(*strpcpy_fn) (char *, char const *);
typedef char *(*strncpy_fn) (char *, char const *, size_t);

static void test_strcpy (char const *);
static void test_strpcpy (char const *);
static void test_strncpy (char const *);

int
main (void)
{
  test_strcpy ("");
  test_strcpy ("abc");
	test_strpcpy ("");
  test_strncpy ("abcdefgh");
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
self_strpcpy (char *dst, char const *src)
{
  char *d = dst;
  while ((*d++ = *src++) != '\0')
    {
      continue;
    }
  return d;
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
test_strcpy (char const *src)
{
  strcpy_fn c_fn = strcpy, self_fn = self_strcpy;
  char *dst1, *dst2;
  size_t len = strlen (src);
  dst1 = malloc (len + 1);
  assert (dst1 != NULL);
  dst2 = malloc (len + 1);
  assert (dst2 != NULL);
  dst1 = c_fn (dst1, src);
  dst2 = self_fn (dst2, src);
  assert (memcmp (dst1, dst2, len) == 0);
  printf ("strcpy: %s\n", dst2);
}

void
test_strpcpy (char const *src)
{
  strcpy_fn c_fn = strcpy, self_fn = self_strcpy;
  char *dst1, *dst2;
  size_t len = strlen (src);
  dst1 = malloc (len + 1);
  assert (dst1 != NULL);
  dst2 = malloc (len + 1);
  assert (dst2 != NULL);
  dst1 = c_fn (dst1, src);
  dst2 = self_fn (dst2, src);
	assert (*dst1 == '\0' && *dst1 == *dst2);
  assert (memcmp (dst1, dst2, len) == 0);
  printf ("strpcpy: %s\n", dst2);
}

void
test_strncpy (char const *src)
{
  strncpy_fn c_fn = strncpy, self_fn = self_strncpy;
  char *dst1, *dst2;
  size_t len = strlen (src);

  dst1 = malloc (len * 2);
  assert (dst1 != NULL);
  dst2 = malloc (len * 2);
  assert (dst2 != NULL);

	dst1 = c_fn (dst1, src, len);
  dst2 = self_fn (dst2, src, len);
  assert (memcmp (dst1, dst2, len) == 0);

  dst1 = c_fn (dst1, src, len + 1);
  dst2 = self_fn (dst2, src, len + 1);
  assert (memcmp (dst1, dst2, len + 1) == 0);
  printf ("strncpy: %s\n", dst2);

  dst1 = c_fn (dst1, src, len + 2);
  dst2 = self_fn (dst2, src, len + 2);
  assert (memcmp (dst1, dst2, len + 2) == 0);
  assert (*(dst1 + len + 1) == '\0' && *(dst1 + len + 1) == *(dst2 + len + 1));
  printf ("strncpy: %s\n", dst2);
}
