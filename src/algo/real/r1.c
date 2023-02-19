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
  uint32_t val : R_VAL_N;
  uint32_t fix : R_FIX_N;
#else
  uint32_t fix : R_FIX_N;
  uint32_t val : R_VAL_N;
#endif
} real_t;


real_t   real_from_int(int);
int      real_to_int(real_t);
int      real_eq(real_t, real_t);
real_t   real_add(real_t, real_t);
real_t   real_mul(real_t, real_t);
real_t   real_div(real_t, real_t);
char    *rtos(real_t, char*, size_t);


int
main(void)
{
  real_t r53 = real_from_int(53);
  assert(real_eq(r53, real_from_int(53)));

  real_t r54 = real_from_int(53+1);
  assert(real_eq((real_add(r53, real_from_int(1))), r54));

  real_t r2 = real_from_int(2);
  real_t r26 = real_from_int(26);
  real_t r52 = real_from_int(52);
  real_t q26 = real_div(r53, r2);

  assert(real_eq(r52, real_mul(r26, r2)));
  assert(real_eq(r53, real_mul(q26, r2)));

  real_t r3 = real_from_int(3);
  real_t r78 = real_from_int(78);
  assert(real_eq(r78, real_mul(r26, r3)));

  char ss[16];

  for (int i = 1; i < 10; i++)
    {
      real_t ri = real_from_int(i);
      real_t qi = real_div(r52, ri);
      printf("52/%d = %16s\n", i, rtos(qi, ss, _nof_(ss)));
    }

  return 0;
}


char*
rtos(real_t r, char *str, size_t size)
{
  int    i;
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
  snprintf(str, size, "%u.%u", r.val, x);

  return str;
}


real_t
real_from_int(int a)
{
  uint32_t   x  =  a << R_FIX_N;
  real_t  r  =  *(real_t*)((uint32_t*) &x);
  return r;
}

int
real_to_int(real_t r)
{
  uint32_t  x  =  *(uint32_t*)((real_t*) &r);
  return x >> R_FIX_N;
}

int
real_eq(real_t a, real_t b)
{
  uint32_t  x  =  *(uint32_t*)((real_t*) &a);
  uint32_t  y  =  *(uint32_t*)((real_t*) &b);
  return x == y;
}

real_t
real_add(real_t a, real_t b)
{
  uint32_t  x  =  *(uint32_t*)((real_t*) &a);
  uint32_t  y  =  *(uint32_t*)((real_t*) &b);
  uint32_t  r  =  x + y;
  return *(real_t*) &r;
}

real_t
real_mul(real_t a, real_t b)
{
  uint32_t  x  =  *(uint32_t*)((real_t*) &a);
  uint32_t  y  =  *(uint32_t*)((real_t*) &b);
  uint32_t  r  =  x * y;
  r >>= R_FIX_N;
  return *((real_t*) &r);
}

real_t
real_div(real_t a, real_t b)
{
  uint32_t  x  =  *(uint32_t*)((real_t*) &a);
  uint32_t  y  =  *(uint32_t*)((real_t*) &b);
  uint32_t  r  =  (x << R_FIX_N) / y;
  return *(real_t*)((uint32_t*) &r);
}
