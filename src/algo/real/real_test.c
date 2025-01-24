#include "../_algo_.h"
#include "real.h"
#include <math.h>

static void test_real_value (void);
static void test_real_from_decimal (void);
static void test_sum (void);

int
main (void)
{
  test_real_value ();
  test_real_from_decimal ();
  test_sum ();
  return 0;
}

void
test_real_value (void)
{
  float f;

  f = -0.1f;
  assert (is_sign ((struct Real const *)&f));

  f = NAN;
  assert (is_nan ((struct Real const *)&f));

  f = -1.0f / 0.0f;
  assert (is_inf ((struct Real const *)&f)
          && is_sign ((struct Real const *)&f));

  f = -0.0f;
  assert (is_zero ((struct Real const *)&f)
          && is_sign ((struct Real const *)&f));
}

void
test_real_from_decimal (void)
{
  struct Real *r = new_real ();

  assert (from_decimal (false, 4, 0, r) && (4.0f == *(float *)r));

  assert (from_decimal (false, 5, 0, r) && (5.0f == *(float *)r));

  assert (from_decimal (false, 5, 2, r) && (500.0f == *(float *)r));

  assert (from_decimal (false, 68, -2, r) && (0.68f == *(float *)r));

  assert (from_decimal (false, 68, -4, r) && (0.0068f == *(float *)r));

  assert (from_decimal (false, 314, -2, r) && (3.14f == *(float *)r));

  assert (from_decimal (false, 3214, -2, r) && (32.14f == *(float *)r));

  assert (from_decimal (true, 1, 0, r) && (-1.0f == *(float *)r));

  assert (from_decimal (true, 314, -2, r) && (-3.14f == *(float *)r));
}

void
test_sum (void)
{
  struct Real *r1 = new_real ();
  struct Real *r2 = new_real ();
  struct Real *r3 = new_real ();

  /* from_decimal (false, 4, 0, r1); */
  /* from_decimal (false, 2, 0, r2); */
  /* assert (sum (r1, r2, r3) && (6.0f == *(float *)r3)); */

  /* from_decimal (false, 0, 0, r1); */
  /* from_decimal (false, 3, 14, r2); */
  /* assert (sum (r1, r2, r3) && (0.0f + 3.14f == *(float *)r3)); */

  from_decimal (false, 5, 0, r1);
  from_decimal (true, 314, -2, r2);
  assert (sum (r1, r2, r3) && (5.0f - 3.14f == *(float *)r3));
}
