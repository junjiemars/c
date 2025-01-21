#include "../_algo_.h"
#include "real.h"
#include <strings.h>

/* bias = 2^{k-1} - 1 */
#define BIAS 0x7f
#define SIGN_WIDTH 1
#define EXPONENT_WIDTH 8
#define MANTISSA_WIDTH 23
#define REAL_WIDTH (SIGN_WIDTH + EXPONENT_WIDTH + MANTISSA_WIDTH)

/* R = (-1)^s \cdot M \cdot 2^E */
struct Real
{
  uint32_t mantissa : MANTISSA_WIDTH;
  uint32_t exponent : EXPONENT_WIDTH;
  uint32_t sign : SIGN_WIDTH;
};

static uint32_t fraction_to_binary (uint32_t);
static uint32_t fraction_sum_shift (int32_t, int32_t, int32_t *);
static bool is_normal (struct Real *);
static bool is_subnormal (struct Real *);

#if !(NM_HAVE_FLSL)
static int flsl (long);
#endif

bool
real_from_decimal (bool sign, unsigned int whole, unsigned int fraction,
                   struct Real *real)
{
  int shift;
  uint32_t w, f, i, r;

  w = whole;
  f = fraction_to_binary (fraction);

  if ((i = flsl (w)) > 0)
    {
      shift = i - 1;
      f >>= shift;
      w <<= MANTISSA_WIDTH - shift;
    }
  else
    {
      i = flsl (f);
      shift = -(i > 0 ? (REAL_WIDTH + 1 - i) : 0);
      f <<= -shift;
    }

  if (f & (1 << EXPONENT_WIDTH))
    {
      r = fraction_sum_shift (f >> (REAL_WIDTH - MANTISSA_WIDTH), 1, &shift);
      f = r << (REAL_WIDTH - MANTISSA_WIDTH);
    }
  f >>= REAL_WIDTH - MANTISSA_WIDTH;

  f |= w;
  shift += BIAS;

  real->sign = sign;
  real->exponent = shift;
  real->mantissa = f;
  return true;
}

bool
real_add (struct Real *lhs, struct Real *rhs, struct Real *sum)
{
  int diff, neg, shift;
  uint32_t sign;
  struct Real r1, r2;

  diff = lhs->exponent - rhs->exponent;
  if (diff < 0)
    {
      r1 = *rhs;
      r2 = *lhs;
      diff = -diff;
    }
  else
    {
      r1 = *lhs;
      r2 = *rhs;
    }

  sign = r1.sign;
  neg = r1.sign != r2.sign ? -1 : 1;

  r1.exponent -= diff;
  r1.mantissa <<= diff;
  shift = 0;
  r1.mantissa = fraction_sum_shift (r1.mantissa, neg * r2.mantissa, &shift);
  if (shift < 0)
    {
      r1.mantissa <<= -shift;
    }
  r1.exponent += shift;

  sum->sign = sign;
  sum->exponent = r1.exponent;
  sum->mantissa = r1.mantissa;

  return true;
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
fraction_sum_shift (int32_t m1, int32_t m2, int32_t *shift)
{
  int32_t f = m1 + m2;
  *shift += f >> MANTISSA_WIDTH;
  return f;
}

__attribute__ ((unused)) bool
is_normal (struct Real *real)
{
  struct Real r1;
  r1.exponent = ~0;
  return !(real->exponent == 0 || real->exponent == r1.exponent);
}

__attribute__ ((unused)) bool
is_subnormal (struct Real *real)
{
  return real->exponent == 0 && real->mantissa > 0;
}

#if !(NM_HAVE_FLSL)
int
flsl (long x)
{
  int i;
  if (x == 0)
    {
      return 0;
    }
  i = 1;
  while ((x & 1) == 0)
    {
      x >>= 1;
      i++;
    }
	return i;
}
#endif
