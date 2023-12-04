#include "_lang_.h"
#include <locale.h>

void print_LC_ALL (void);
void test_setlocale (const char *);
void test_strcoll (const char *);

int
main (int argc, char **argv)
{
  char *locale = "";
  if (argc > 1)
    {
      locale = argv[1];
    }
  test_setlocale (locale);
  test_strcoll (locale);
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
test_strcoll (const char *locale)
{
  int rc;
  const char *s1 = "café";
  const char *s2 = "caffè";
  setlocale (LC_ALL, locale);
  rc = strcoll (s1, s2);
  printf ("%s %s %s\n", s1, (rc < 0) ? "<" : rc == 0 ? "=" : ">", s2);
}
