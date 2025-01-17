#include "../_algo_.h"
#include "real.h"

static void test_real_from_decimal (void);
static void test_real_add (void);

int
main (void)
{
  test_real_from_decimal ();
  test_real_add ();
  return 0;
}

void
test_real_from_decimal (void)
{
  struct Real *r = new_real ();

  if (real_from_decimal (4, 0, r))
    {
      assert (4.0f == *(float *)r);
    }

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

void
test_real_add (void)
{
  struct Real *r1 = new_real ();
  struct Real *r2 = new_real ();
  struct Real *r3 = new_real ();

  real_from_decimal (4, 0, r1);
  real_from_decimal (2, 0, r2);
  if (real_add (r1, r2, r3))
    {
      assert (6.0f == *(float *)r3);
    }

  real_from_decimal (3, 14, r2);
  if (real_add (r1, r2, r3))
    {
      assert (4.0f + 3.14f == *(float *)r3);
    }
}
