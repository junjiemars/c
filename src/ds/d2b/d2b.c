#include "../_ds_.h"
#include "stack.h"
#include <stdio.h>

void
test_d2b (int n, int g)
{
  stack_s *s = stack_new (0, sizeof (int) * 8, sizeof (char));
  unsigned int u = n;
  for (size_t i = 0; i < sizeof (int) * 8; i++)
    {
      unsigned int x = u % 2;
      stack_push (s, &x);
      u /= 2;
    }

  printf ("%i to binary\n--------------------\n", n);
  int g1 = 1;
  while (stack_pop (s, &u))
    {
      printf ("%i", u);
      if (0 == (g1 % g))
        {
          printf (" ");
        }
      g1++;
    };
  putchar ('\n');

  stack_free (s);
}

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stderr, "which number convert to binary?\n");
      return 0;
    }

  int n, g;
  sscanf (argv[1], "%d, %d", &n, &g);
  test_d2b (n, g);

  return 0;
}
