#include <_algo_.h>
#include "real.h"
#include <math.h>

static void test_special_quantity (void);
static void test_from_decimal (void);
static void test_add (void);
static void test_mul (void);

int
main (void)
{
  test_special_quantity ();
  test_from_decimal ();
  test_add ();
  test_mul ();
  return 0;
}

void
test_special_quantity (void)
{
  float f;

  f = -0.1f;
  assert (is_sign ((struct Real const *)&f));

  f = NAN;
  assert (is_nan ((struct Real const *)&f));

#if !(MSVC)
  f = -1.0f / 0.0f;
  assert (is_inf ((struct Real const *)&f)
          && is_sign ((struct Real const *)&f));
#endif

  f = -0.0f;
  assert (is_zero ((struct Real const *)&f)
          && is_sign ((struct Real const *)&f));
}

void
test_from_decimal (void)
{
  struct Real *r = new_real ();

  assert (from_decimal (false, 0, 0, r) && (0.0f == *(float *)r));

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
test_add (void)
{
  struct Real *r1 = new_real ();
  struct Real *r2 = new_real ();
  struct Real *r3 = new_real ();

  from_decimal (false, 101, -1, r1);
  from_decimal (true, 993, -2, r2);
  assert (add (r1, r2, r3) && (10.1f - 9.93f == *(float *)r3));

  /* from_decimal (false, 4, 0, r1); */
  /* from_decimal (false, 25, -2, r2); */
  /* assert (add (r1, r2, r3) && (4.25f == *(float *)r3)); */

  /* from_decimal (false, 0, 0, r1); */
  /* from_decimal (false, 314, -2, r2); */
  /* assert (add (r1, r2, r3) && (0.0f + 3.14f == *(float *)r3)); */

  /* from_decimal (false, 4, 0, r1); */
  /* from_decimal (true, 314, -2, r2); */
  /* assert (add (r1, r2, r3) && (4.0f - 3.14f == *(float *)r3)); */

  /* from_decimal (false, 5, 0, r1); */
  /* from_decimal (true, 314, -2, r2); */
  /* assert (add (r1, r2, r3) && ((5.0f - 3.14f) == *(float *)r3)); */
}

void
test_mul (void)
{
  struct Real *r1 = new_real ();
  struct Real *r2 = new_real ();
  struct Real *r3 = new_real ();

  /* from_decimal (false, 2, 0, r1); */
  /* from_decimal (false, 3, 0, r2); */
  /* assert (mul (r1, r2, r3) && (2.0f * 3.0f == *(float *)r3)); */

  from_decimal (false, 2, 0, r1);
  from_decimal (false, 25, -2, r2);
  assert (mul (r1, r2, r3) && (2.0f * 0.25f == *(float *)r3));
}
