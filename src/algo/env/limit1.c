#include "../_algo_.h"
#include <float.h>
#include <limits.h>

#define LIMIT_U_MAX(t) ((t)~0)
#define LIMIT_U_MIN(t) (0)

#define LIMIT_S_MAX(t) (((t)1 << (sizeof (t) * CHAR_BIT - 1)) - 1)
#define LIMIT_S_MIN(t) ((t)(-(LIMIT_S_MAX (t)) - 1))

static int char_bit (void);
static float float_min (void);
static float float_max (void);
static double double_min (void);
static double double_max (void);
static long double long_double_min (void);
static long double long_double_max (void);

int
main (void)
{
  assert (CHAR_BIT == char_bit ());

  if (!_isut_ (char))
    {
      assert (CHAR_MIN == LIMIT_S_MIN (char));
      assert (CHAR_MAX == LIMIT_S_MAX (char));
    }
  assert (UCHAR_MAX == LIMIT_U_MAX (unsigned char));

  assert (SHRT_MAX == LIMIT_S_MAX (short));
  assert (SHRT_MIN == LIMIT_S_MIN (short));
  assert (USHRT_MAX == LIMIT_U_MAX (unsigned short));

  assert (INT_MIN == LIMIT_S_MIN (int));
  assert (INT_MAX == LIMIT_S_MAX (int));
  assert (UINT_MAX == LIMIT_U_MAX (unsigned int));

  assert (LONG_MIN == LIMIT_S_MIN (long));
  assert (LONG_MAX == LIMIT_S_MAX (long));
  assert (ULONG_MAX == LIMIT_U_MAX (unsigned long));

  assert (LLONG_MIN == LIMIT_S_MIN (long long));
  assert (LLONG_MAX == LIMIT_S_MAX (long long));
  assert (ULLONG_MAX == LIMIT_U_MAX (unsigned long long));

  assert (FLT_MIN == float_min ());
  assert (FLT_MAX == float_max ());

  assert (DBL_MIN == double_min ());
  assert (DBL_MAX == double_max ());

  assert (LDBL_MIN == long_double_min ());
  assert (LDBL_MAX == long_double_max ());

  return 0;
}

int
char_bit (void)
{
  int n = 0;
	char c = 1;
	while (c)
		{
			c <<= 1;
			n++;
		}
  return n;
}

float
float_min (void)
{
  union
  {
    float f;
    uint32_t u;
  } u1;
  u1.u = 1 << 23;
  return u1.f;
}

float
float_max (void)
{
  union
  {
    float f;
    uint32_t u;
  } u1;
  u1.u = (uint32_t)0x00fe << 23 | (uint32_t)0x007fffff;
  return u1.f;
}

double
double_min (void)
{
  union
  {
    double d;
    uint64_t u;
  } u1;
  u1.u = (uint64_t)1 << 52;
  return u1.d;
}

double
double_max (void)
{
  union
  {
    double d;
    uint64_t u;
  } u1;
  u1.u = (uint64_t)0x07fe << 52 | (uint64_t)0x000fffffffffffff;
  return u1.d;
}

long double
long_double_min (void)
{
  union
  {
    long double d;
    uint64_t u;
  } u1;
  u1.u = (uint64_t)1 << 52;
  return u1.d;
}

long double
long_double_max (void)
{
  union
  {
    long double d;
    uint64_t u;
  } u1;
  u1.u = (uint64_t)0x07fe << 52 | (uint64_t)0x000fffffffffffff;
  return u1.d;
}
