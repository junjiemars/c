#include "../_lang_.h"

int
main (__attribute__ ((unused)) int argc, __attribute__ ((unused)) char **argv,
      __attribute__ ((unused)) char **envp)
{
  char **p = envp;

  printf ("char **envp ...\n----------\n");
  while (*p)
    {
      printf ("%s\n", *p++);
    }

  return 0;
}
