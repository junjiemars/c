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
  struct Real *r = new_real ();
  float f = 5;

  if (real_from_decimal (5, 0, r))
    {
      assert (f == *(float *)r);
    }

  f = 0.68;
  if (real_from_decimal (0, 68, r))
    {
      assert (f == *(float *)r);
    }

  f = 3.14;
  if (real_from_decimal (3, 14, r))
    {
      assert (f == *(float *)r);
    }
}
