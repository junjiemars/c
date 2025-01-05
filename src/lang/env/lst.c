#include "../_lang_.h"

extern char **environ;

int
main (int argc, char **argv)
{
  (void)(argc);
  (void)(argv);

  printf ("environ at 0x%p\n----------\n", (void *)environ);

  for (char *p = *environ; p; p = *++environ)
    {
      printf ("%s\n", *environ);
    }

  return 0;
}
