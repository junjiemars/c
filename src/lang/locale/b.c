#include "../_lang_.h"
#include <locale.h>

static void print_LC_ALL (void);
static void test_setlocale (const char *);
static void test_strcmp (const char *, const char *);
static void test_strcoll (const char *, const char *);
static void test_strxfrm (const char *);

int
main (int argc, char **argv)
{
  char *locale = "";
  const char *s1 = "café";
  const char *s2 = "caffè";

  if (argc > 1)
    {
      locale = argv[1];
    }
  test_setlocale (locale);
  test_strcmp (s1, s2);
  test_strcoll (s1, s2);
  test_strxfrm (s2);
  return 0;
}

void
print_LC_ALL (void)
{
  static char text[128];
  time_t t = time (0);
  printf ("%.3f\n", 31415.9265354);
  strftime (text, sizeof (text), "%A, %B, %d, %Y(%x)", localtime (&t));
  puts (text);
}

void
test_setlocale (const char *locale)
{
  char *cur, *old;
  cur = setlocale (LC_ALL, NULL);
  old = strdup (cur);
  setlocale (LC_ALL, locale);
  cur = setlocale (LC_ALL, NULL);
  printf ("LC_ALL=%s <- %s\n----------\n", cur, old);
  free (old);
  print_LC_ALL ();
}

void
test_strcmp (const char *s1, const char *s2)
{
  int c = strcmp (s1, s2);
  printf ("strcmp(%s,%s) = %d\n", s1, s2, c);
}

void
test_strcoll (const char *s1, const char *s2)
{
  int c;
  c = strcoll (s1, s2);
  printf ("strcoll(%s,%s) = %d\n", s1, s2, c);
}

void
test_strxfrm (const char *s2)
{
  char s1[BUFSIZ];
  size_t c;
  c = strxfrm (s1, s2, BUFSIZ);
  printf ("strxfrm(%s,%s) = %zu\n", s1, s2, c);
}
