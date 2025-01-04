#include "math1.h"
#include <assert.h>
#include <geo.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int
main (void)
{
  double a = area_of_rect (4., 5.);
  assert (a == 20 && "aref of rect 4*5 should be 20");

  // trunc toward to zero
  assert (1 == trunc (1.5) && -1 == trunc (-1.5)
          && "trunc should toward to zero");

  // floor toward to -infinite
  assert (1 == floor (1.5) && -2 == floor (-1.5)
          && "floor should to -infinite");

  // ceil toward to +infinite
  assert (2 == ceil (1.5) && -1 == ceil (-1.5)
          && "ceil should toward to +infinite");

  /*
    round: return the integral value nearest to x rounding
    half-way cases away from zero, regardless of the
    current rounding direction.
  */
  assert (1 == round (1.4) && -1 == round (-1.4)
          && "nearest and rounding half-away");
  assert (2 == round (1.5) && -2 == round (-1.5)
          && "nearest and rounding half-away");

  return 0;
}
