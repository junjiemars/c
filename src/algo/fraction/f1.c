#include "../_algo_.h"
#include <gcd.h>

typedef struct Fraction
{
  int num;
  int deno;
} Fraction;

Fraction from (int, int);
Fraction add (Fraction, Fraction);
Fraction mul (Fraction, Fraction);

static Fraction *reduce (Fraction *);

int
main (void)
{
  Fraction f1 = from (1, 3);
  Fraction f2 = from (3, 4);
  Fraction r = add (f1, f2);
  assert (r.num == 13 && r.deno == 12);

  f1 = from (3, 4);
  f2 = from (-2, 4);
  r = add (f1, f2);
  assert (r.num == 1 && r.deno == 4);

  f1 = from (2, 4);
  f2 = from (3, 8);
  r = mul (f1, f2);
  assert (r.num == 3 && r.deno == 16);

	/* divide */
	f2 = from (f2.deno, f2.num);
	r = mul (f1, f2);
	assert (r.num == 4 && r.deno == 3);

  return 0;
}

Fraction
from (int num, int deno)
{
  return (Fraction){ .num = num, .deno = deno };
}

Fraction
add (Fraction a, Fraction b)
{
  Fraction sum;
  sum.num = a.num * b.deno + b.num * a.deno;
  sum.deno = a.deno * b.deno;
  (void)reduce (&sum);
  return sum;
}

Fraction
mul (Fraction a, Fraction b)
{
  Fraction prod;
  prod.num = a.num * b.num;
  prod.deno = a.deno * b.deno;
  (void)reduce (&prod);
  return prod;
}

Fraction *
reduce (Fraction *a)
{
  int d = gcd (a->num, a->deno);
  a->num /= d;
  a->deno /= d;
  return a;
}
