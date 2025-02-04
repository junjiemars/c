#ifndef _POINT_H_
#define _POINT_H_

typedef struct Point
{
  double x;
  double y;
} Point;

Point new_point (double x, double y);
int point_eq (Point const *p1, Point const *p2);
double point_distance (Point const *p1, Point const *p2);
void point_to_polar (Point const *p, double *radial, double *theta);

#endif /* _POINT_H_ */
