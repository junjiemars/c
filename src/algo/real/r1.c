#include "_algo_.h"

/*
 * https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html
 *
 */


#define R_FIX_T  uint64_t
#define R_VAL_T  int64_t
#define R_FIX_N  16
#define R_VAL_N  48
#define R_FIX_F  PRIu64
#define R_VAL_F  PRIi64



typedef struct real_s
{
#if (NM_HAVE_LITTLE_ENDIAN)
  R_VAL_T val : R_VAL_N;
  R_FIX_T fix : R_FIX_N;
#else
  R_FIX_T fix : R_FIX_N;
  R_VAL_T val : R_VAL_N;
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
  printf("precision: 0b%d/0d%d, width: %zuB\n------------\n",
         R_FIX_N, R_FIX_N/4, sizeof(real_t));

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
  printf("%d = %16s\n", real_to_int(r53), rtos(r53, ss, _nof_(ss)));

  assert(real_eq(r1n, r1n));
  assert(-1 == real_to_int(r1n));
  printf("%d = %16s\n", real_to_int(r1n), rtos(r1n, ss, _nof_(ss)));

  assert(-2 == real_to_int(r2n));
  printf("%d = %16s\n", real_to_int(r2n), rtos(r2n, ss, _nof_(ss)));
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

      printf("%02d/%03d = %20s %20s*%03d = %20s\n",
             real_to_int(r53), i, qs, qs, i, ps);
    }
}

char*
rtos(real_t r, char *str, size_t size)
{
  R_FIX_T         sum           =  0;
  static R_FIX_T  fix[R_FIX_N]  =  {0};

  if (fix[0] == 0)
    {
      /* $\sum_{i=1}^{P} 5^i \cdot 10^{P-i}$ */
      for (R_FIX_T i = 0; i < R_FIX_N; i++)
        {
          R_FIX_T  p5   =  1;
          R_FIX_T  p10  =  1;

          for (R_FIX_T j = 0; j < (R_FIX_N - i - 1); j++)
            {
              p10 *= 10;
            }

          for (R_FIX_T k = 0; k <= i; k++)
            {
              p5 *= 5;
            }

          fix[i] = p5 * p10;
        }
    }

  for (R_FIX_T i = 0; i < R_FIX_N; i++)
    {
      if (r.fix & (1 << (R_FIX_N - i - 1)))
        {
          sum += fix[i];
        }
    }

  snprintf(str, size, "%"R_VAL_F".%"R_FIX_F, (R_VAL_T) r.val, (R_FIX_T) sum);

  return str;
}


real_t
real_from_int(int a)
{
  R_VAL_T  x  =  a << R_FIX_N;
  return *((real_t*) &x);
}

int
real_to_int(real_t r)
{
  R_VAL_T  x  =  *((R_VAL_T*) &r);
  return (int) (x >> R_FIX_N);
}

int
real_eq(real_t a, real_t b)
{
  R_VAL_T  x  =  *((R_VAL_T*) &a);
  R_VAL_T  y  =  *((R_VAL_T*) &b);
  return x == y;
}

real_t
real_add(real_t a, real_t b)
{
  R_VAL_T  x  =  *((R_VAL_T*) &a);
  R_VAL_T  y  =  *((R_VAL_T*) &b);
  R_VAL_T  r  =  x + y;
  return *(real_t*) &r;
}

real_t
real_mul(real_t a, real_t b)
{
  R_VAL_T  x  =  *((R_VAL_T*) &a);
  R_VAL_T  y  =  *((R_VAL_T*) &b);
  R_VAL_T  r  =  x * y;
  r >>= R_FIX_N;
  return *((real_t*) &r);
}

real_t
real_div(real_t a, real_t b)
{
  R_VAL_T  x  =  *((R_VAL_T*) &a);
  R_VAL_T  y  =  *((R_VAL_T*) &b);
  R_VAL_T  r  =  (x << R_FIX_N) / y;
  return *((real_t*) &r);
}
