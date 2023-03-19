#include "d.h"
#include <stdio.h>

int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <words...>\n");
      return 1;
    }

  char *s = longest_common_prefix(&argv[1], argc - 1);
  printf("%s\n", s);

  return 0;
}
