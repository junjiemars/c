#include "d.h"
#include <stdio.h>


int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <int>\n");
      return 1;
    }

  int n = atoi(argv[1]);
  char *s = int_to_words(n);
  printf("%d = %s\n", n, s);

  free(s);


  return 0;
}
