#include "../_lang_.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define print_range(min, max)                                                 \
  printf ("ranged random [%i, %i)\n------------\n", (min), (max))

static size_t randomize (size_t n /* RAND_MAX */);
static int ranged_randomize (int min, int max);

int
main (int argc, char **argv)
{
  int n;
  int min = 0, max = 10;

  if (argc < 2)
    {
      fprintf (stderr, "please input: <N> [,MIN] [,MAX]\n");
      return 1;
    }

  /* N */
  n = atoi (argv[1]);

  /* MIN */
  if (argc >= 3)
    {
      min = atoi (argv[2]);
    }

  /* MAX */
  if (argc >= 4)
    {
      max = atoi (argv[3]);
    }

  /* initialize random number generator */
  srand ((unsigned)time (0));

  print_range (0, n);

  for (int i = 0; i < n; i++)
    {
      printf ("%zu ", randomize (n));
    }
  putchar ('\n');

  print_range (min, max);

  for (int i = 0; i < n; i++)
    {
      printf ("%i ", ranged_randomize (min, max));
    }
  putchar ('\n');

  return 0;
}

size_t
randomize (size_t n)
{
  size_t r = rand () % n;
  return r;
}

int
ranged_randomize (int min, int max)
{
  int r = min + (int)(rand () / (RAND_MAX + 1.0) * (max - min));
  return r;
}
