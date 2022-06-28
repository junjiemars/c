#include <stdio.h>

extern char **environ;

int
main(void)
{
  char  **ss;

  ss = environ;

  while (*ss)
    {
      printf("%-16p->%16p: %s\n", ss, *ss, *ss);
      ss++;
    }

  return 0;
}
