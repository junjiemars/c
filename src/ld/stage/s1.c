#include "_ld_.h"
/* #include "f1.h" */


extern int n_status;
extern float add_and_mul(int, int);

int
main(void)
{
  float  x  =  1.0;
  float  y  =  5.0;
  float  z;

  z = add_and_mul(x, y);

  return 0;
}
