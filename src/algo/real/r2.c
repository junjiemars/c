#include "../_algo_.h"
#include "real.h"
#include <limits.h>

#define BIAS 0x7f
#define SIGN_WIDTH 1
#define EXPONENT_WIDTH 8
#define MANTISSA_WIDTH 23
#define REAL_WIDTH (SIGN_WIDTH + EXPONENT_WIDTH + MANTISSA_WIDTH)

#define EXPONENT_MAX (BIAS + BIAS)
#define EXPONENT_MIN (-BIAS - 1)
#define REAL_SIGN_MAX (((1 << EXPONENT_WIDTH) - 1) << MANTISSA_WIDTH)
#define REAL_UNSIGN_MAX (((1 << (EXPONENT_WIDTH + 1)) - 1) << MANTISSA_WIDTH)

#if (NM_HAVE_FFSL || NM_HAVE_FLSL)
#include <strings.h>
#endif

#if (GCC)
#pragma GCC diagnostic ignored "-Woverflow"
#endif

/**
 * $Real = (-1)^s \cdot 2^e \cdot m$
 * $e_{min} \le e \le e_{max} \text{ with } e_{min} = 1 - e_{max}$
 * $m = d_0 . d_1 d_2 d_3 \ldots d_{p-1} \text{ with } 0 \le d_i < 2$
 */
struct Real
{
#if (NM_CPU_LITTLE_ENDIAN)
  union
  {
    struct
    {
      uint32_t mantissa : MANTISSA_WIDTH;
      uint32_t exponent : EXPONENT_WIDTH;
      uint32_t sign : SIGN_WIDTH;
    };
    uint32_t magnitude;
  };
#else
  union
  {
    uint32_t magnitude;
    struct
    {
      uint32_t sign : SIGN_WIDTH;
      uint32_t exponent : EXPONENT_WIDTH;
      uint32_t mantissa : MANTISSA_WIDTH;
    };
  };
#endif
};

static uint32_t fraction_to_binary (uint32_t, int);
static uint32_t fraction_sum_shift (int32_t, int32_t, int32_t *);
static void normalize (uint32_t, int *);
static bool is_subnormal (struct Real *);

#if !(NM_HAVE_FFSL)
int ffsl (long);
#endif /* ffsl */
#if !(NM_HAVE_FLSL)
int flsl (long);
#endif /* flsl */

bool
from_decimal (bool sign, unsigned whole, int scale, struct Real *real)
{
  int shift;
  uint32_t w, f, i, r;

  if (whole == 0)
    {
      *real = (struct Real){ 0 };
      return true;
    }

  w = whole;
  f = 0;
  if (scale < 0)
    {
      f = 1;
      for (int s = scale; s; s++)
        {
          w /= 10;
          f *= 10;
        }
      r = w > 0 ? whole - w * f : whole;
      f = fraction_to_binary (r, -scale);
    }
  else if (scale > 0)
    {
      for (; scale; scale--)
        {
          w *= 10;
        }
    }

  if ((i = flsl (w)) > 0)
    {
      shift = i - 1;
      f >>= shift;
      w <<= MANTISSA_WIDTH - shift;
    }
  else
    {
      i = flsl (f);
      shift = -1 * (i > 0 ? (REAL_WIDTH + 1 - i) : 0);
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
add (struct Real const *lhs, struct Real const *rhs, struct Real *sum)
{
  int diff, e;
  uint32_t s, m1, m2;
  struct Real r1, r2;

  if (is_zero (lhs))
    {
      *sum = *rhs;
      return true;
    }
  else if (is_zero (rhs))
    {
      *sum = *lhs;
      return true;
    }

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

  s = r1.sign;
  e = r1.exponent;
  m1 = r1.mantissa;
  m2 = r2.mantissa;

  m1 = (m1 & ((1 << MANTISSA_WIDTH) - 1)) | (1 << MANTISSA_WIDTH);
  m2 = (m2 & ((1 << MANTISSA_WIDTH) - 1)) | (1 << MANTISSA_WIDTH);
  m2 >>= diff;

  if (r1.sign == r2.sign)
    {
      m1 += m2;
    }
  else
    {
      if (m1 >= m2)
        {
          m1 -= m2;
        }
      else
        {
          m1 = m2 - m1;
          s = r2.sign;
        }
    }

  while (m1 >= (1 << (MANTISSA_WIDTH + 1)))
    {
      m1 >>= 1;
      e += 1;
    }

  while (m1 < (1 << MANTISSA_WIDTH))
    {
      m1 <<= 1;
      e -= 1;
    }

  if (e > EXPONENT_MAX)
    {
      sum->magnitude = s ? REAL_SIGN_MAX : REAL_UNSIGN_MAX;
      return false;
    }
  else if (e < EXPONENT_MIN)
    {
      sum->magnitude = 0;
      return false;
    }
  m1 &= ((1 << MANTISSA_WIDTH) - 1);

  sum->sign = s;
  sum->exponent = e;
  sum->mantissa = m1;

  return true;
}

bool
mul (struct Real const *lhs, struct Real const *rhs, struct Real *product)
{
  int e;
  uint32_t s, m, m1, m2;
  struct Real r1, r2;

  if (is_zero (lhs))
    {
      *product = *rhs;
      return true;
    }
  else if (is_zero (rhs))
    {
      *product = *lhs;
      return true;
    }

  r1 = *lhs;
  r2 = *rhs;
  s = r1.sign ^ r2.sign;
  e = r1.exponent + r2.exponent - BIAS;
  m1 = (r1.mantissa & ((1 << MANTISSA_WIDTH) - 1)) | (1 << MANTISSA_WIDTH);
  m2 = (r2.mantissa & ((1 << MANTISSA_WIDTH) - 1)) | (1 << MANTISSA_WIDTH);
  m = m1 * m2;

  normalize (m, &e);

  if (e > EXPONENT_MAX)
    {
      product->magnitude = s ? REAL_SIGN_MAX : REAL_UNSIGN_MAX;
      return false;
    }
  else if (e < EXPONENT_MIN)
    {
      product->magnitude = 0;
      return false;
    }
  m &= ((1 << MANTISSA_WIDTH) - 1);

  product->sign = s;
  product->exponent = e;
  product->mantissa = m;
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
fraction_to_binary (uint32_t fraction, int scale)
{
  uint32_t s, i, m, f, f10;

  f10 = 1;
  for (f = fraction, s = scale; f || s; f /= 10, s--)
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

void
normalize (uint32_t mantissa, int *exponent)
{
  for (; mantissa >= (1 << (MANTISSA_WIDTH)); mantissa >>= 1)
    {
      *exponent += 1;
    }

  for (; mantissa && mantissa < (1 << (MANTISSA_WIDTH)); mantissa <<= 1)
    {
      *exponent -= 1;
    }
}

bool
is_normal (struct Real const *real)
{
  struct Real r1;
  r1.exponent = ~(uint32_t)0;
  return !(real->exponent == 0 || real->exponent == r1.exponent);
}

__attribute__ ((unused)) bool
is_subnormal (struct Real *real)
{
  return real->exponent == 0 && real->mantissa > 0;
}

bool
is_sign (struct Real const *real)
{
  return (*(uint32_t *)real >> (EXPONENT_WIDTH + MANTISSA_WIDTH)) & 1;
}

bool
is_nan (struct Real const *real)
{
  struct Real r1;
  r1.exponent = ~(uint32_t)0;
  return real->exponent == r1.exponent && real->mantissa > 0;
}

bool
is_inf (struct Real const *real)
{
  struct Real r1;
  r1.exponent = ~(uint32_t)0;
  return real->exponent == r1.exponent && real->mantissa == 0;
}

bool
is_zero (struct Real const *real)
{
  return real->exponent == 0 && real->mantissa == 0;
}

#if !(NM_HAVE_FFSL)
int
ffsl (long a)
{
  int i;
  if (a == 0)
    {
      return 0;
    }
  for (i = 1; a; a >>= 1, i++)
    {
      if (a & 1)
        {
          return i;
        }
    }
  return 0;
}
#endif /* ffsl */

#if !(NM_HAVE_FLSL)
int
flsl (long a)
{
  int i;
  size_t n;

  if (a == 0)
    {
      return 0;
    }

  n = sizeof (long) * CHAR_BIT;
  for (i = (int)n; i; i--)
    {
      if (a & ((long)1 << (long)(i - 1)))
        {
          break;
        }
    }
  return i;
}
#endif /* flsl */
