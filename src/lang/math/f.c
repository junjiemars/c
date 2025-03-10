/**
 * https://courses.cs.northwestern.edu/213/slides/04-FloatingPoint.pdf
 * https://courses.cs.washington.edu/courses/cse401/01au/details/fp.html
 * https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
 * https://www-users.cse.umn.edu/~vinals/tspot_files/phys4041/2020/IEEE%20Standard%20754-2019.pdf
 * https://www.cs.umd.edu/~meesh/411/CA-online/chapter/floating-point-arithmetic-unit/index.html
 * https://www.jhauser.us/arithmetic/SoftFloat.html
 * https://www2.math.uconn.edu/~leykekhman/courses/MATH3795/Lectures/Lecture_2_Floating_point.pdf
 */
#include "../_lang_.h"
#include <float.h>
#include <math.h>

#if defined(BIT8_SUF)
#undef BIT8_SUF
#endif
#define BIT8_SUF "\n"
#include <nbits.h>

#if defined(BIT8_SEP)
#undef BIT8_SEP
#define BIT8_SEP " "
#endif

#if defined(BIT16_SEP)
#undef BIT16_SEP
#define BIT16_SEP " "
#endif

static uint32_t to_ui (float);
static uint64_t to_ul (double);

static void test_cmp_float (void);
static void test_cmp_double (void);
static void test_asm_double (void);
static void test_asm_long_double (void);
static void test_epsilon_double (void);
static void test_double_zero (void);
static void test_double_equal (void);
static void test_double_classify (void);
static void test_double_round (void);

int
main (void)
{
  test_cmp_float ();
  test_cmp_double ();
  test_asm_double ();
  test_asm_long_double ();
  test_epsilon_double ();
  test_double_zero ();
  test_double_equal ();
  test_double_classify ();
  test_double_round ();

  return 0;
}

uint32_t
to_ui (float x)
{
  uint32_t u;
  memcpy ((char *)&u, (char *)&x, sizeof (x));
  assert (u == *(uint32_t *)&x && "bit pattern copy should be equal");
  return u;
}

uint64_t
to_ul (double x)
{
  uint64_t u;
  memcpy ((char *)&u, (char *)&x, sizeof (x));
  assert (u == *(uint64_t *)&x && "bit pattern copy should be equal");
  return u;
}

void
test_cmp_float (void)
{
  float d1 = 0.1f, d2 = 0.2f, d3 = 0.3f;
  uint32_t u1 = to_ui (d1);
  uint32_t u2 = to_ui (d2);
  uint32_t u12 = to_ui (d1 + d2);
  uint32_t u3 = to_ui (d3);

  printf ("compare float\n--------------------\n");
  printf ("%16f = 0x%X\n", d1, u1);
  printf ("%16f = 0x%X\n", d2, u2);
  printf ("%16f = 0x%X\n", d1 + d2, u12);
  printf ("%16f = 0x%X\n", d3, u3);

  printf (BPRI32, BIT32 (u1));
  printf (BPRI32, BIT32 (u2));
  printf (BPRI32, BIT32 (u12));
  printf (BPRI32, BIT32 (u3));

  assert (u3 == u12);
  assert (d3 == d1 + d2);

  __attribute__ ((unused)) int less;
  __attribute__ ((unused)) int greater;
  __attribute__ ((unused)) int lessgreater;
  __attribute__ ((unused)) int unordered;
  __attribute__ ((unused)) int lessequal;
  __attribute__ ((unused)) int greaterequal;

  less = isless (d3, d1 + d2);
  greater = isgreater (d3, d1 + d2);
  lessgreater = islessgreater (d3, d1 + d2);
  lessequal = islessequal (d3, d1 + d2);
  greaterequal = isgreaterequal (d3, d1 + d2);
  unordered = isunordered (d3, d1 + d2);

  assert (!unordered);
  assert (!less);
  assert (!greater);
  assert (!lessgreater);
  assert ((less || greater) == lessgreater);
  assert (lessequal && greaterequal);

  __attribute__ ((unused)) int less1;
  __attribute__ ((unused)) int greater1;
  __attribute__ ((unused)) int lessgreater1;

  float lg1 = 0.1f, lg2 = 0.2f, lg3 = 0.3001f;
  less1 = isless (lg3, lg1 + lg2);
  greater1 = isgreater (lg3, lg1 + lg2);
  lessgreater1 = islessgreater (lg3, lg1 + lg2);

  assert (less1 || greater1);
  assert (lessgreater1);
  assert ((less1 || greater1) == lessgreater1);
}

void
test_cmp_double (void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  uint64_t u1 = to_ul (d1);
  uint64_t u2 = to_ul (d2);
  uint64_t u12 = to_ul (d1 + d2);
  uint64_t u3 = to_ul (d3);

  printf ("compare double\n--------------------\n");
  printf ("%16lf = 0x%llX\n", d1, (unsigned long long)to_ul (d1));
  printf ("%16lf = 0x%llX\n", d2, (unsigned long long)to_ul (d2));
  printf ("%16lf = 0x%llX\n", d1 + d2, (unsigned long long)to_ul (d1 + d2));
  printf ("%16lf = 0x%llX\n", d3, (unsigned long long)to_ul (d3));

  printf (BPRI64, BIT64 ((unsigned long long)u1));
  printf (BPRI64, BIT64 (u2));
  printf (BPRI64, BIT64 (u12));
  printf (BPRI64, BIT64 (u3));

  assert (u3 != u12);
  assert (d3 != d1 + d2);

  __attribute__ ((unused)) int less;
  __attribute__ ((unused)) int greater;
  __attribute__ ((unused)) int lessgreater;
  __attribute__ ((unused)) int unordered;
  __attribute__ ((unused)) int lessequal;
  __attribute__ ((unused)) int greaterequal;
  less = isless (d3, d1 + d2);
  greater = islessgreater (d3, d1 + d2);
  lessgreater = islessgreater (d3, d1 + d2);
  lessequal = islessequal (d3, d1 + d2);
  greaterequal = isgreaterequal (d3, d1 + d2);
  unordered = isunordered (d3, d1 + d2);

  assert (less);
  assert (greater);
  assert (lessgreater);
  assert (lessequal || greaterequal);
  assert (less && greater);

  __attribute__ ((unused)) int less1;
  __attribute__ ((unused)) int greater1;
  __attribute__ ((unused)) int lessgreater1;
  double lg1 = 0.1, lg2 = 0.2, lg3 = 0.3001;
  less1 = isless (lg3, lg1 + lg2);
  greater1 = isgreater (lg3, lg1 + lg2);
  lessgreater1 = islessgreater (lg3, lg1 + lg2);

  assert (less1 || greater1);
  assert (lessgreater1);
  assert ((less1 || greater1) == lessgreater1);
}

void
test_asm_double (void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  __attribute__ ((unused)) int x = (int)((d1 + d2) - d3);
}

void
test_asm_long_double (void)
{
  long double d1 = 0.1L, d2 = 0.2L, d3 = 0.3L;
  __attribute__ ((unused)) int x = (int)((d1 + d2) - d3);
}

void
test_epsilon_double (void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  double epsilon = DBL_EPSILON;
  __attribute__ ((unused)) int x = fabs ((d1 + d2) - d3) < epsilon;
  assert (x);
}

void
test_double_zero (void)
{
  double d1 = 0.0, d2 = 0.0;
  __attribute__ ((unused)) int le;
  __attribute__ ((unused)) int ge;

  le = islessequal (d1, d2);
  ge = isgreaterequal (d1, d2);

  assert (FP_ZERO == fpclassify (d1));
  assert (d1 == d2);
  assert (le && ge);
}

void
test_double_equal (void)
{
  double d1 = 0.1, d2 = 0.2, d3 = 0.3;
  __attribute__ ((unused)) int le;
  __attribute__ ((unused)) int ge;
  __attribute__ ((unused)) int l;
  __attribute__ ((unused)) int g;

  le = islessequal (d1 + d2, d3);
  ge = isgreaterequal (d1 + d2, d3);
  l = isless (d1 + d2, d3);
  g = isgreater (d1 + d2, d3);

  assert ((le || ge) && (l || g));
  assert (g && ge);
}

void
test_double_classify (void)
{
  assert (FP_ZERO == fpclassify (0.0));
  assert (FP_ZERO == fpclassify (0.0 / DBL_MAX));
  assert (FP_NORMAL == fpclassify (1.0));
  assert (FP_NORMAL != fpclassify (0.0));

#if !defined(MSVC)
  assert (FP_INFINITE == fpclassify (1.0 / 0.0));
  assert (FP_INFINITE == fpclassify (-1.0 / 0.0));
  assert (FP_NAN == fpclassify ((1.0L / 0.0) / (1.0 / 0.0)));
#endif

  assert (isfinite (0.0));
#if !defined(MSVC)
  assert (isinf (1.0 / 0.0));
  assert (isnan ((1.0 / 0.0) / (1.0 / 0.0)));
#endif
  assert (isnormal (0.1));
}

void
test_double_round (void)
{
  char decimal[][64]
      = { "3.1415926535897932384626433832795028841971693993751058209749" };

  printf ("round double\n------------\n");

  for (size_t i = 0; i < _nof_ (decimal); i++)
    {
      printf ("decimal:     %s\n", decimal[i]);
      printf ("hexadecimal: %a\n", strtod (decimal[i], NULL));
    }
}
