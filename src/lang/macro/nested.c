#include "../_lang_.h"

#define SQUARE(x) ((x) * (x))
#define CUBE(x) (SQUARE (x) * (x))

int
main (void)
{
  int x = SQUARE (3 + 3);
  int y = CUBE (3 + 3);

  printf ("square(3)=%i, cube(3)=%i\n", x, y);

  return 0;
}
