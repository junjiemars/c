#include "_ld_.h"
#include "f1.h"

extern int n_status;

int
main(void)
{
  float  x  =  1.0;
  float  y  =  5.0;
  float  z;

  z = add_and_mul(x, y);
  n_status = 1;

  return 0;
}
