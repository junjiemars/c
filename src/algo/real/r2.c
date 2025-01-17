#include "real.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>

/* bias = 2^{k-1} - 1 */
#define BIAS 0x7f
#define SIGN_WIDTH 1
#define EXPONENT_WIDTH 8
#define MANTISSA_WIDTH 23
#define REAL_WIDTH (sizeof (uint32_t) * 8)

/* R = (-1)^s \cdot M \cdot 2^E */
struct Real
{
  uint32_t mantissa : MANTISSA_WIDTH;
  uint32_t exponent : EXPONENT_WIDTH;
  uint32_t sign : SIGN_WIDTH;
};

int
real_from_decimal (int whole, unsigned int fraction, struct Real *real)
{
  int shift;
  uint32_t s, w, f;
  uint32_t i, m, f10;

  s = whole < 0 ? 1 : 0;
  w = s ? -whole : whole;

  f10 = 1;
  for (f = fraction; f > 0; f /= 10)
    {
      f10 *= 10;
    }

  i = m = 0;
  f = fraction;
  while (f > 0 && f < f10 && i < REAL_WIDTH)
    {
      i++;
      f <<= 1;
      if (f >= f10)
        {
          f -= f10;
          m += 1 << (REAL_WIDTH - i);
        }
    }

  if ((i = flsl (w)) > 0)
    {
      shift = i - 1;
      m >>= shift;
      w >>= shift;
      w <<= MANTISSA_WIDTH - shift;
    }
  else
    {
      i = flsl (m);
      shift = -(i > 0 ? (REAL_WIDTH + 1 - i) : i);
      m <<= -shift;
    }

  if (m & (1 << EXPONENT_WIDTH))
    {
      m |= 1 << (EXPONENT_WIDTH + 1);
    }
  m >>= REAL_WIDTH - MANTISSA_WIDTH;

  /* TODO: round again */
  m |= w & ((1 << MANTISSA_WIDTH) - 1);

  shift = shift ? shift + BIAS : 0;

  real->sign = s;
  real->exponent = shift;
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
