#include "real.h"
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define BIAS 0x7f
#define LEN_MANTISSA 23

struct Real
{
  uint32_t mantissa : LEN_MANTISSA;
  uint32_t exponent : 8;
  uint32_t sign : 1;
};

struct Real *
real_from_decimal (int sign, int exponent, int mantissa)
{
  struct Real *r;
  r = calloc (1, sizeof (struct Real));
  if (!r)
    {
      return NULL;
    }
  *r = (struct Real){
    .sign = sign,
    .exponent = exponent + BIAS,
    .mantissa = 1 << (LEN_MANTISSA - mantissa + 1),
  };
  return r;
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
