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

  if (real_from_decimal (5, 0, r))
    {
      assert (5.0f == *(float *)r);
    }

  if (real_from_decimal (0, 68, r))
    {
      assert (0.68f == *(float *)r);
    }

  if (real_from_decimal (3, 14, r))
    {
      assert (3.14f == *(float *)r);
    }

  if (real_from_decimal (32, 14, r))
    {
      assert (32.14f == *(float *)r);
    }
}
