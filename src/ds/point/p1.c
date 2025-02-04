#include "point.h"
#include <math.h>
#include <stdlib.h>

Point
new_point (double x, double y)
{
  return (Point){ .x = x, .y = y };
}

int
point_eq (Point const *p1, Point const *p2)
{
  return p1->x == p2->x && p1->y == p2->y;
}

double
point_distance (Point const *p1, Point const *p2)
{
  double x, y;
  x = p1->x - p2->x;
  y = p1->y - p2->y;
  return sqrt (x * x + y * y);
}

void
point_to_polar (Point const *p, double *r, double *theta)
{
  *r = sqrt (p->x * p->x + p->y * p->y);
  *theta = atan2 (p->y, p->x);
}
