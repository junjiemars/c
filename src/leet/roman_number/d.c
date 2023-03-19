#include "d.h"
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <roman number>\n");
      return 1;
    }

  int n = roman_to_int(argv[1]);
  printf("%s = %d\n", argv[1], n);

  char *s = int_to_roman(n);
  printf("%d = %s\n", n, s);

  free(s);

  return 0;
}
