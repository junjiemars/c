#include "real.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

#define BIAS 0x7f
#define LEN_MANTISSA 23

struct Real
{
  uint32_t mantissa : LEN_MANTISSA;
  uint32_t exponent : 8;
  uint32_t sign : 1;
};

int
real_from_decimal (int whole, unsigned int fraction, struct Real *real)
{
  uint32_t s, w, f;
  uint32_t w2, f10;
  uint32_t i, m;

  s = whole < 0 ? 1 : 0;
  w = s ? -whole : whole;

  f10 = 1;
  for (f = fraction; f > 0; f /= 10)
    {
      f10 *= 10;
    }

  i = 0;
  m = 0;
  f = fraction;
  while (f > 0 && f < f10 && i < (LEN_MANTISSA + 1))
    {
      f *= 2;
      i++;
      if (f >= f10)
        {
          m += 1 << (LEN_MANTISSA - i);
          f -= f10;
        }
    }
  m += w << LEN_MANTISSA;
  i = flsl ((long)m);
  w2 = i - (LEN_MANTISSA + 1);
  if (i > (LEN_MANTISSA + 1))
    {
      m >>= i - (LEN_MANTISSA + 1);
    }
  else
    {
      m <<= (LEN_MANTISSA + 1) - i;
    }

  real->sign = s;
  real->exponent = w2 + BIAS;
  real->mantissa = m & 0x7fffff;
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
