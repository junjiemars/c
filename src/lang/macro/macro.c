#include "macro.h"
#include "../_lang_.h"

#define double_v1(x) 2 * x
#define double_v2(x) (2 * (x))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define check_blank(a) strlen (#a)

#define incr_v1(a, b)                                                         \
  (a)++;                                                                      \
  (b)++;

#define incr_v2(a, b)                                                         \
  do                                                                          \
    {                                                                         \
      (a)++;                                                                  \
      (b)++;                                                                  \
    }                                                                         \
  while (0) /* no ; at tail */

#define sum(max, out)                                                         \
  do                                                                          \
    {                                                                         \
      /* avoid name clash */                                                  \
      int total_g123 = 0;                                                     \
      int max_g124 = max;                                                     \
      for (int i_g125 = 0; i_g125 < max_g124; i_g125++)                       \
        total_g123 += i_g125;                                                 \
      out = total_g123;                                                       \
    }                                                                         \
  while (0)

#define square(x) ((x) * (x))
#define cube(x) (square (x) * (x))

#if (NM_HAVE_VARIADIC_MACRO)
#if (NM_HAVE_SPRINTF_S)
#define io_sprintf(b, ...) sprintf_s (b, sizeof (b), __VA_ARGS__)
#elif NM_HAVE_SNPRINTF_S
#define io_sprintf(b, ...) snprintf (b, sizeof (b), __VA_ARGS__)
#else
#define io_sprintf(b, ...) sprintf (b, __VA_ARGS__)
#endif
#endif /* NM_HAVE_VARIADIC_MACRO */

static void test_double_macro (void);
static void test_max_macro (void);
static void test_incr_macro (void);
static void test_sum_macro (void);
static void test_blank_macro (void);
static void test_variadic_macro (void);
static void test_nested_macro (void);
static void test_variadic_macro (void);

int
main (void)
{
  test_double_macro ();
  test_max_macro ();
  test_incr_macro ();
  test_sum_macro ();
  test_blank_macro ();
  test_nested_macro ();
  test_variadic_macro ();

  return 0;
}

void
test_double_macro (void)
{
  printf ("\ndouble macro\n");
  printf ("--------------\n");
  printf ("double_v1(1+1)*8=%i\n", double_v1 (1 + 1) * 8);
  printf ("double_v2(1+1)*8=%i\n", double_v2 (1 + 1) * 8);
}

void
test_max_macro (void)
{
  int a = 1, b = 2;

  printf ("\nmax macro\n");
  printf ("-----------\n");

  printf ("a=%i, b=%i, |+ max\n", a, b);
  printf ("max(a,b++)=%i\n", max (a, b++));
  printf ("a=%i, b=%i, |- max\n", a, b);
}

void
test_incr_macro (void)
{
  int a = 1, b = 2;

  printf ("\nincr macro\n");
  printf ("------------\n");
  printf ("a=%i, b=%i, |+ incr_v1\n", a, b);

  {
    incr_v1 (a, b);
  }
  printf ("if (a > b) incr_v1(a, b)\n");
  printf ("a=%i, b=%i, |- incr_v1\n", a, b);

  printf ("------------\n");
  a = 2, b = 1;
  printf ("a=%i, b=%i, |+ incr_v2\n", a, b);

  {
    incr_v2 (a, b);

    {
      printf ("a=%i, b=%i, when a > b is flase\n", a, b);
    }
    printf ("a=%i, b=%i, |- incr_v2\n", a, b);
  }
}

void
test_sum_macro (void)
{
  printf ("\nsum macro\n");
  printf ("-----------\n");
  int total = 5, out;
  printf ("sum(5, out)\n");
  sum (5, out);
  printf ("out=%i, total=%i, |-  sum(%i)\n", out, total, 5);
  int i = 5;
  sum (i, out);
  printf ("out=%i, total=%i, |-- sum(%i)\n", out, total, i);
}

void
test_blank_macro (void)
{
  printf ("\ncheck_blank macro\n");
  printf ("-------------------\n");
#if !defined(MSVC)
  /* C4003: not enough actual parameters for macro 'check_blank' */
  printf ("'%s' is blank strlen=%zu\n", "", check_blank ());
#endif /* MSVC */
  printf ("strlen(%s)=%zu\n", "123", check_blank (123));
  printf ("strlen(%s)=%zu\n", "abcd", check_blank (abcd));
}

void
test_nested_macro (void)
{
  int x = square (3 + 3);
  int y = cube (3 + 3);

  printf ("\nnested macro\n");
  printf ("------------------\n");

  printf ("square(3)=%i, cube(3)=%i\n", x, y);
}

void
test_variadic_macro (void)
{
  printf ("\nvariadic macro\n");
  printf ("------------------\n");

#if (NM_HAVE_VARIADIC_MACRO)
#define test_vm_sprintf(...) sprintf (__VA_ARGS__)
#define test_vm_args(...) puts (#__VA_ARGS__)

  char buf[sizeof (short)];

  test_vm_sprintf (buf, "%c", '1');
  assert ('1' == buf[0]);

  test_vm_args (first, second, third);
#else
  printf ("!no variadic macro");

#endif /* NM_HAVE_VARIADIC_MACRO */
}
