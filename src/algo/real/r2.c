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

static uint32_t fraction_to_binary (uint32_t);
static uint32_t fraction_sum_shift (uint32_t, uint32_t, int *);

int
real_from_decimal (int whole, unsigned int fraction, struct Real *real)
{
  int shift;
  uint32_t s, w, i, m;

  s = whole < 0 ? 1 : 0;
  w = s ? -whole : whole;

  m = fraction_to_binary (fraction);

  if ((i = flsl (w)) > 0)
    {
      shift = i - 1;
      m >>= shift;
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

  m |= w;
  m &= (1 << MANTISSA_WIDTH) - 1;
  shift = shift ? shift + BIAS : 0;

  real->sign = s;
  real->exponent = shift;
  real->mantissa = m;
  return 1;
}

int
real_add (struct Real *lhs, struct Real *rhs, struct Real *sum)
{
  int shift;
  uint32_t round;
  struct Real r1, r2;

  shift = lhs->exponent - rhs->exponent;
  if (shift < 0)
    {
      r1 = *rhs;
      r2 = *lhs;
      shift = -shift;
    }
  else
    {
      r1 = *lhs;
      r2 = *rhs;
    }

  r2.sign = 0;
  r2.exponent -= BIAS;
	round = (r2.mantissa & (1 << EXPONENT_WIDTH)) == (1 << EXPONENT_WIDTH);
  *(uint32_t *)&r2 >>= shift;
  r2.mantissa = fraction_sum_shift (r2.mantissa, r1.mantissa, &shift);
  r2.mantissa = fraction_sum_shift (r2.mantissa, round, &shift);

  sum->sign = r1.sign;
  sum->exponent = r1.exponent;
  sum->mantissa = r2.mantissa;

  return 1;
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

uint32_t
fraction_to_binary (uint32_t fraction)
{
  uint32_t i, m, f, f10;

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
  return m;
}

uint32_t
fraction_sum_shift (uint32_t m1, uint32_t m2, int *shift)
{
  uint32_t f = m1 + m2;
  *shift += f >> MANTISSA_WIDTH;
  return f;
}
