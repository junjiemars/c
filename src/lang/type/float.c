#include "../_lang_.h"

static void test_float_type (void);
static void test_average (void);
static double average (double, double, double);

int
main (void)
{
  test_float_type ();
  test_average ();

  return 0;
}

void
test_float_type (void)
{
  float f = 3.14f;
  double d = 2.7182; /* non suffix means double */
  long double ld = 2.718281828459L;

  printf ("%20s=%02zu, %020f, 0x%016x\n", "sizeof(float)", sizeof (f), f,
          *(unsigned int *)&f);

  printf ("%20s=%02zu, %020lf, 0x%16lx\n", "sizeof(double)", sizeof (d), d,
          *(unsigned long *)&d);

  printf ("%20s=%02zu, %020Lf, 0x%16llx\n", "sizeof(long double)", sizeof (ld),
          ld, *(unsigned long long *)&ld);
}

double
average (double a, double b, double c)
{
  return (a + b + c) / 3;
}

void
test_average (void)
{
  double a, b, c;

  a = 1.0;
  b = 2.0;
  c = 3.0;

  printf ("average(%f, %f, %f) = %f\n", a, b, c, average (a, b, c));
}
