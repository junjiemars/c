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

  assert (real_from_decimal (false, 4, 0, r) && (4.0f == *(float *)r));

  assert (real_from_decimal (false, 5, 0, r) && (5.0f == *(float *)r));

  assert (real_from_decimal (false, 0, 68, r) && (0.68f == *(float *)r));

  assert (real_from_decimal (false, 3, 14, r) && (3.14f == *(float *)r));

  assert (real_from_decimal (false, 32, 14, r) && (32.14f == *(float *)r));

  assert (real_from_decimal (true, 1, 0, r) && (-1.0f == *(float *)r));

  assert (real_from_decimal (true, 3, 14, r) && (-3.14f == *(float *)r));
}

void
test_real_add (void)
{
  struct Real *r1 = new_real ();
  struct Real *r2 = new_real ();
  struct Real *r3 = new_real ();

  /* real_from_decimal (false, 4, 0, r1); */
  /* real_from_decimal (false, 2, 0, r2); */
  /* assert (real_add (r1, r2, r3) && (6.0f == *(float *)r3)); */

  /* real_from_decimal (false, 4, 0, r1); */
  /* real_from_decimal (false, 3, 14, r2); */
  /* assert (real_add (r1, r2, r3) && (4.0f + 3.14f == *(float *)r3)); */

  real_from_decimal (false, 5, 0, r1);
  real_from_decimal (true, 3, 14, r2);
  assert (real_add (r1, r2, r3) && (5.0f - 3.14f == *(float *)r3));
}
