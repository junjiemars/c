#include "_lang_.h"


/*
 * Note:
 *
 * 1. '#' convert expression to string
 *
 * 2. '%g' format double
 *
 * 3. the length of pointer just equals sizeof(int)
 *
 * 4. sizeof EXPR, sizeof(TYPE).
 *
 */

#define  peval(expr)  printf("%-32s: %04zuB\n", #expr, expr);


int
main(void)
{
  peval(sizeof(double));

  double  d = 1.0;
  peval(sizeof d + 10);

  peval(sizeof(int));
  peval(sizeof sizeof(int));

  double a[] = {1, 2, 3};
  peval(sizeof(a)/(sizeof(*a)));

  return 0;
}
