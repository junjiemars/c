#include "real.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#define BIAS 0x7f
#define LEN_EXPONENT 8
#define LEN_MANTISSA 23
#define LEN_REAL (sizeof (uint32_t) * 8)

struct Real
{
  uint32_t mantissa : LEN_MANTISSA;
  uint32_t exponent : LEN_EXPONENT;
  uint32_t sign : 1;
};

int
real_from_decimal (int whole, unsigned int fraction, struct Real *real)
{
  int shift;
  uint32_t s, w, f;
  uint32_t i, m, f10;

  s = whole < 0 ? 1 : 0;
  w = s ? -whole : whole;

  i = flsl (w);
  shift = i > 0 ? i - 1 : -1;

  f10 = 1;
  for (f = fraction; f > 0; f /= 10)
    {
      f10 *= 10;
    }

  i = m = 0;
  f = fraction;
  while (f > 0 && f < f10 && i < LEN_REAL)
    {
      f *= 2;
      i++;
      if (f >= f10)
        {
          f -= f10;
          m += 1 << (LEN_REAL - i);
        }
    }

  i = flsl (m);
  shift = shift > 0 ? shift : shift - (i - LEN_REAL);
  if (shift < 0)
    {
      m <<= -shift;
    }
  else
    {
      m >>= shift;
      w <<= LEN_MANTISSA - shift;
    }
  if (m & (1 << LEN_EXPONENT))
    {
      m |= 1 << (LEN_EXPONENT + 1);
    }
  m >>= LEN_REAL - LEN_MANTISSA;
  m |= w & 0x7fffff;

  real->sign = s;
  real->exponent = shift + BIAS;
  real->mantissa = m;
  return 1;
}

struct Real *
real_add (__attribute__ ((unused)) struct Real *lhs,
          __attribute__ ((unused)) struct Real *rhs)
{
  return 0;
}

char *
real_str (__attribute__ ((unused)) struct Real *real,
          __attribute__ ((unused)) char *buf,
          __attribute__ ((unused)) size_t bufsize)
{
  return 0;
}

void
free_real (struct Real *real)
{
  free (real);
}

struct Real *
new_real (void)
{
  return calloc (1, sizeof (struct Real));
}
