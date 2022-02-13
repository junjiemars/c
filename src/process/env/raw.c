#include <stdio.h>

extern char **environ;

int
main(void)
{
  while (*environ)
    {
      printf("%s\n", *environ++);
    }

  return 0;
}
