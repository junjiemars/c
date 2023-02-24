#include "_algo_.h"

/*
 * https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html
 *
 */


#define R_FIX_N  8
#define R_VAL_N  24


typedef struct real_s
{
#if (NM_HAVE_LITTLE_ENDIAN)
  int32_t  val : R_VAL_N;
  uint32_t fix : R_FIX_N;
#else
  uint32_t fix : R_FIX_N;
  int32_t  val : R_VAL_N;
#endif
} real_t;


real_t   real_from_int(int);
int      real_to_int(real_t);
int      real_eq(real_t, real_t);
real_t   real_add(real_t, real_t);
real_t   real_mul(real_t, real_t);
real_t   real_div(real_t, real_t);
char    *rtos(real_t, char*, size_t);

static void  test_literal(void);
static void  test_arith(void);


int
main(void)
{
  test_literal();
  test_arith();

  return 0;
}

void
test_literal(void)
{
  char    ss[32];
  real_t  r53  =  real_from_int(53);
  real_t  r1n  =  real_from_int(-1);
  real_t  r2n  =  real_from_int(-2);

  assert(real_eq(r53, r53));
  assert(53 == real_to_int(r53));
  printf("%s = %16s\n", _str_(52), rtos(r53, ss, _nof_(ss)));

  assert(real_eq(r1n, r1n));
  assert(-1 == real_to_int(r1n));
  printf("%s = %16s\n", _str_(-1), rtos(r1n, ss, _nof_(ss)));

  assert(-2 == real_to_int(r2n));
  printf("%s = %16s\n", _str_(-2), rtos(r2n, ss, _nof_(ss)));
}

void
test_arith(void)
{
  int     i;
  char    ss1[32], ss2[32];
  real_t  r53  =  real_from_int(53);

  for (i = 10; i >= -10; i--)
    {
      if (i == 0)
        {
          continue;
        }

      real_t r = real_from_int(i);
      real_t q = real_div(r53, r);
      real_t p = real_mul(q, r);

      char *qs = rtos(q, ss1, _nof_(ss1));
      char *ps = rtos(p, ss2, _nof_(ss2));

      printf("%d / %03d = %16s    %16s * %03d = %16s\n",
             real_to_int(r53), i, qs, qs, i, ps);
    }
}

char*
rtos(real_t r, char *str, size_t size)
{
  uint32_t  i;
  uint32_t  x             =  0, y;
  static uint32_t  fix[]  =
    {
        390625,   781250,  1562500,  3125000,
       6250000, 12500000, 25000000, 50000000
    };

  for (y = r.fix, i = 0; y; y >>= 1, i++)
    {
      if (r.fix & (1 << i))
        {
          x += fix[i];
        }
    }
  snprintf(str, size, "%d.%u", r.val, x);

  return str;
}


real_t
real_from_int(int a)
{
  int32_t  x  =  a << R_FIX_N;
  real_t   r  =  *(real_t*)((int32_t*) &x);
  return r;
}

int
real_to_int(real_t r)
{
  int32_t  x  =  *(int32_t*)((real_t*) &r);
  return x >> R_FIX_N;
}

int
real_eq(real_t a, real_t b)
{
  int32_t  x  =  *(int32_t*)((real_t*) &a);
  int32_t  y  =  *(int32_t*)((real_t*) &b);
  return x == y;
}

real_t
real_add(real_t a, real_t b)
{
  int32_t  x  =  *(int32_t*)((real_t*) &a);
  int32_t  y  =  *(int32_t*)((real_t*) &b);
  int32_t  r  =  x + y;
  return *(real_t*) &r;
}

real_t
real_mul(real_t a, real_t b)
{
  int32_t  x  =  *(int32_t*)((real_t*) &a);
  int32_t  y  =  *(int32_t*)((real_t*) &b);
  int32_t  r  =  x * y;
  r >>= R_FIX_N;
  return *((real_t*) &r);
}

real_t
real_div(real_t a, real_t b)
{
  int32_t  x  =  *(int32_t*)((real_t*) &a);
  int32_t  y  =  *(int32_t*)((real_t*) &b);
  int32_t  r  =  (x << R_FIX_N) / y;
  return *(real_t*)((int32_t*) &r);
}
