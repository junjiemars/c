#include "_lang_.h"

int
main (int argc, char **argv)
{
  printf ("\niterate **argv via for loop (char*)[]:\n----------\n");
  for (int i = 0; i < argc; i++)
    {
      printf ("%s ", argv[i]);
    }

  printf ("\niterate **argv via for loop char**:\n----------\n");
  for (char **p = argv; p < argv + argc; p++)
    {
      printf ("%s ", *p);
    }

  printf ("\niterate **argv via while loop char**:\n----------\n");
  char **p = argv;
  while (*p)
    {
      printf ("%s ", *p++);
    }

  /* C99: return 0; */
}
