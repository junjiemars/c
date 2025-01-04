#include "_lang_.h"
#include <locale.h>

static void print_locale (const char *);

int
main (void)
{
  printf ("current locale:\n------------\n");
  print_locale (0);

  printf ("env locale:\n------------\n");
  print_locale ("");
}

void
print_locale (const char *locale)
{
  printf ("%s=%s\n", _str_ (LC_COLLATE), setlocale (LC_COLLATE, locale));

  printf ("%s=%s\n", _str_ (LC_CTYPE), setlocale (LC_CTYPE, locale));

  printf ("%s=%s\n", _str_ (LC_MONETARY), setlocale (LC_MONETARY, locale));

  printf ("%s=%s\n", _str_ (LC_NUMERIC), setlocale (LC_NUMERIC, locale));

  printf ("%s=%s\n", _str_ (LC_TIME), setlocale (LC_TIME, locale));

#ifdef LC_MESSAGES
  printf ("%s=%s\n", _str_ (LC_MESSAGES), setlocale (LC_MESSAGES, locale));
#endif
}
