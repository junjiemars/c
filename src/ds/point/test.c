#include "../_ds_.h"
#include "point.h"
#include <assert.h>

static void test_point (void);

int
main (void)
{
  test_point ();
  return 0;
}

void
test_point (void)
{
  Point p1 = new_point (0.0, 0.0);
  Point p2 = new_point (0.0, 0.0);
  assert (point_eq (&p1, &p2));
  assert (point_distance (&p1, &p2) == 0);

  double radial, theta;
  point_to_polar (&p1, &radial, &theta);
  assert (radial == 0.0 && theta == 0.0);
}
