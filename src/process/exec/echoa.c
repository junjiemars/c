#include "_process_.h"


int
main(int argc, char **argv)
{
  int            i;
  char         **p;
  extern char  **environ;

  for (i = 0; i < argc; i++)
    {
      printf("argv[%d]: %s\n", i, argv[i]);
    }

  for (p = environ; *p != 0; p++)
    {
      printf("%s\n", *p);
    }

  exit(0);
}
