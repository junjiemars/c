#include "_lang_.h"
#include <float.h>
#include <math.h>


#define BIT8_SUF "\n"
#include <nbits.h>

#if (MSVC)
#  pragma warning(disable: 4293)
#endif

#if defined(BIT8_SEP)
#  undef  BIT8_SEP
#  define BIT8_SEP " "
#endif

#if defined(BIT16_SEP)
#  undef  BIT16_SEP
#  define BIT16_SEP " "
#endif

unsigned int to_ui(float);
unsigned long to_ul(double);

void test_cmp_float(void);
void test_cmp_double(void);
void test_asm_double(void);
void test_asm_long_double(void);
void test_epsilon_double(void);
void test_double_zero(void);
void test_double_equal(void);
void test_double_classify(void);

unsigned int
to_ui(float x)
{
  unsigned int u;
  memcpy((char*)&u, (char*)&x, sizeof(x));
  return u;
}

unsigned long
to_ul(double x)
{
  unsigned long u;
  memcpy((char*)&u, (char*)&x, sizeof(x));
  return u;
}

void
test_cmp_float(void)
{
  float d1 = 0.1f, d2 = 0.2f, d3 = 0.3f;
  unsigned int u1 = to_ui(d1);
  unsigned int u2 = to_ui(d2);
  unsigned int u12 = to_ui(d1+d2);
  unsigned int u3 = to_ui(d3);

  printf("compare float\n--------------------\n");
  printf("%16f = 0x%X\n", d1, u1);
  printf("%16f = 0x%X\n", d2, u2);
  printf("%16f = 0x%X\n", d1+d2, u12);
  printf("%16f = 0x%X\n", d3, u3);

  printf(BPRI32, BIT32(u1));
  printf(BPRI32, BIT32(u2));
  printf(BPRI32, BIT32(u12));
  printf(BPRI32, BIT32(u3));

  assert(u3 == u12);
  assert(d3 == d1 + d2);

  int less, greater, lessgreater, unordered, lessequal, greaterequal;
  less = isless(d3, d1+d2);
  greater = isgreater(d3, d1+d2);
  lessgreater = islessgreater(d3, d1+d2);
  lessequal = islessequal(d3, d1+d2);
  greaterequal = isgreaterequal(d3, d1+d2);
  unordered = isunordered(d3, d1+d2);

  assert(!unordered);
  assert(!less);
  assert(!greater);
  assert(!lessgreater);
  assert((less || greater) == lessgreater);
  assert(lessequal && greaterequal);

  int less1, greater1, lessgreater1;
  float lg1 = 0.1f, lg2 = 0.2f, lg3 = 0.3001f;
  less1 = isless(lg3, lg1+lg2);
  greater1 = isgreater(lg3, lg1+lg2);
  lessgreater1 = islessgreater(lg3, lg1+lg2);

  assert(less1 || greater1);
  assert(lessgreater1);
  assert((less1 || greater1) == lessgreater1);
}

void
test_cmp_double(void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  unsigned long u1 = to_ul(d1);
  unsigned long u2 = to_ul(d2);
  unsigned long u12 = to_ul(d1+d2);
  unsigned long u3 = to_ul(d3);

  printf("compare double\n--------------------\n");
  printf("%16lf = 0x%lX\n", d1, to_ul(d1));
  printf("%16lf = 0x%lX\n", d2, to_ul(d2));
  printf("%16lf = 0x%lX\n", d1+d2, to_ul(d1+d2));
  printf("%16lf = 0x%lX\n", d3, to_ul(d3));

  printf(BPRI64, BIT64(u1));
  printf(BPRI64, BIT64(u2));
  printf(BPRI64, BIT64(u12));
  printf(BPRI64, BIT64(u3));

  assert(u3 != u12);
  assert(d3 != d1 + d2);

  int less, greater, lessgreater, unordered, lessequal, greaterequal;
  less = isless(d3, d1+d2);
  greater = islessgreater(d3, d1+d2);
  lessgreater = islessgreater(d3, d1+d2);
  lessequal = islessequal(d3, d1+d2);
  greaterequal = isgreaterequal(d3, d1+d2);
  unordered = isunordered(d3, d1+d2);

  assert(!unordered);
  assert(less);
  assert(greater);
  assert(lessgreater);
  assert(lessequal || greaterequal);
  assert(less && greater);

  int less1, greater1, lessgreater1;
  double lg1 = 0.1, lg2 = 0.2, lg3 = 0.3001;
  less1 = isless(lg3, lg1+lg2);
  greater1 = isgreater(lg3, lg1+lg2);
  lessgreater1 = islessgreater(lg3, lg1+lg2);

  assert(less1 || greater1);
  assert(lessgreater1);
  assert((less1 || greater1) == lessgreater1);
}

void
test_asm_double(void)
{
  double                       d1  =  0.1, d2 = 0.2, d3 = 0.3;
  __attribute__((unused)) int  x   =  (int) ((d1+d2) - d3);
}

void
test_asm_long_double(void)
{
  long double                  d1  =  0.1L, d2 = 0.2L, d3 = 0.3L;
  __attribute__((unused)) int  x   =  (int) ((d1+d2) - d3);
}

void
test_epsilon_double(void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  double epsilon = DBL_EPSILON;
  int x = fabs((d1+d2) - d3) < epsilon;
  assert(x);
}

void
test_double_zero(void)
{
  double d1 = 0.0, d2 = 0.0;
  int le, ge;

  le = islessequal(d1, d2);
  ge = isgreaterequal(d1, d2);

  assert(FP_ZERO == fpclassify(d1));
  assert(d1 == d2);
  assert(le && ge);
}

void
test_double_equal(void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  int le, ge, l, g;

  le = islessequal(d1+d2, d3);
  ge = isgreaterequal(d1+d2, d3);
  l = isless(d1+d2, d3);
  g = isgreater(d1+d2, d3);

  assert((le || ge) && (l || g));
  assert(g && ge);
}

void
test_double_classify(void)
{
  assert(FP_ZERO == fpclassify(0.0));
  assert(FP_ZERO == fpclassify(0.0/DBL_MAX));
  assert(FP_NORMAL == fpclassify(1.0));
  assert(FP_NORMAL != fpclassify(0.0));

#if !defined(MSVC)
  assert(FP_INFINITE == fpclassify(1.0/0.0));
  assert(FP_INFINITE == fpclassify(-1.0/0.0));
  assert(FP_NAN == fpclassify((1.0L/0.0) / (1.0/0.0)));
#endif

  assert(isfinite(0.0));
#if !defined(MSVC)
  assert(isinf(1.0/0.0));
  assert(isnan((1.0/0.0)/(1.0/0.0)));
#endif
  assert(isnormal(0.1));
}

int
main(void)
{
  test_cmp_float();
  test_cmp_double();
  test_asm_double();
  test_asm_long_double();
  test_epsilon_double();
  test_double_zero();
  test_double_equal();
  test_double_classify();

  return 0;
}
