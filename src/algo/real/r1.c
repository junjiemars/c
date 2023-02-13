#include "_algo_.h"


typedef struct real_s
{
  struct fixed_s
  {
    unsigned short  width;
    unsigned short  point;
  } fixed;

  int  val;

} real_t;


real_t  real_from_int(int, int);
int     real_to_int(real_t);
int     real_eq(real_t, real_t);
real_t  real_add(real_t, real_t);
real_t  real_div(real_t, real_t);
real_t  real_mul(real_t, real_t);

static void  test_int(void);

int
main(void)
{
  test_int();

  return 0;
}

void
test_int(void)
{
  int  a53  =  53;

  assert(53 == real_to_int(real_from_int(a53, 0)));
  assert(53 == real_to_int(real_from_int(a53, 1)));

  real_t  r53  =  real_from_int(53, 1);
  real_t  r2   =  real_from_int(2, 1);
  assert(real_eq(r53, real_mul(real_div(r53, r2), r2)));

  assert(real_eq(r53, real_add(real_div(r53, r2), real_div(r53, r2))));
}

real_t
real_from_int(int a, int b)
{
  real_t r1 =
    {
      .fixed = { .width = sizeof(unsigned short) * 8, .point = b },
      0,
    };
  r1.val = (a << r1.fixed.point) | b;

  return r1;
}

int
real_to_int(real_t r)
{
  return r.val >> r.fixed.point;
}

int
real_eq(real_t a, real_t b)
{
  assert(a.fixed.width == b.fixed.width && a.fixed.point == b.fixed.point);
  return a.val == b.val;
}

real_t
real_add(real_t a, real_t b)
{
  assert(a.fixed.width == b.fixed.width && a.fixed.point == b.fixed.point);
  a.val += b.val;
  return a;
}

real_t
real_div(real_t a, real_t b)
{
  assert(a.fixed.width == b.fixed.width && a.fixed.point == b.fixed.point);

  a.val >>= b.val;

  return a;
}

real_t
real_mul(real_t a, real_t b)
{
  assert(a.fixed.width == b.fixed.width && a.fixed.point == b.fixed.point);
  a.val <<= b.val;
  a.val >>= a.fixed.point;
  return a;
}
