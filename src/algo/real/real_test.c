#include "../_algo_.h"
#include "real.h"

static void test_real_from_decimal (void);

int
main (void)
{
  test_real_from_decimal ();
  return 0;
}

void
test_real_from_decimal (void)
{
  float f5 = 5;
  struct Real *r5 = real_from_decimal (0, 2, 3);
  assert (*(uint32_t *)&f5 == *(uint32_t *)r5);
  free_real (r5);

  float fn1 = -1;
  struct Real *rn1 = real_from_decimal (1, 0, 0);
  assert (*(uint32_t *)&fn1 == *(uint32_t *)rn1);
  free_real (rn1);
}
