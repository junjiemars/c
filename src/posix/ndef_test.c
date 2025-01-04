#include "ndef.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

static void test_unused (int);
static void test_unused_fn (void);
static void test_fallthrough (int);

static void test_restrict (const int *restrict, const char *restrict);
static void test_static_assert (void);
static void test_alignof (void);
static void test_alignas (void);
static void test_generic (void);

static void test_str (void);
static void test_cat (void);
static void test_isut (void);
static void test_nof (void);
static void test_swp (void);

int
main (int argc, char **argv)
{
  test_unused (1);
  test_fallthrough (1);

  test_restrict ((const int *restrict)&argc, (const char *restrict)argv[0]);
  test_static_assert ();

#if (NM_HAVE_ALIGNOF)
  test_alignof ();
#else
  printf ("!no `alignof' found\n");
#endif

#if (NM_HAVE_ALIGNAS)
  test_alignas ();
#else
  printf ("!no `alignas' found\n");
#endif

  test_generic ();

  test_str ();
  test_cat ();
  test_isut ();
  test_nof ();
  test_swp ();

  return 0;
}

void
test_unused (__attribute__ ((unused)) int a)
{
  __attribute__ ((unused)) int b;
  /* void */
}

__attribute__ ((unused)) void
test_unused_fn (void)
{
  /* void */
}

void
test_fallthrough (int a)
{
  switch (a)
    {
    case 0:
      __attribute__ ((fallthrough));
    case 1:
      break;
    }
}

void
test_restrict (__attribute__ ((unused)) const int *restrict ii,
               __attribute__ ((unused)) const char *restrict ss)
{
#if !(NM_HAVE_RESTRICT)
  printf ("%s no `restrict' found\n");
#else
  assert (ii != 0 && ss != 0);
#endif
}

void
test_static_assert (void)
{
#if !(NM_HAVE_STATIC_ASSERT)
  printf ("%s no `static_assert' found\n");
#else
  static_assert (sizeof (char) == 1, "sizeof(char) must be 1 byte");
#endif
}

void
test_alignof (void)
{
  struct X
  {
    char c;
    int i;
  };

  size_t alignof_char = alignof (char);
  assert (alignof_char == 1);
  assert (alignof (short) == 2);
  assert (alignof (int) == 4);
  assert (alignof (int *) == 8);
  assert (alignof (char[8]) == alignof (char));
  assert (alignof (short[8]) == alignof (short));
  assert (alignof (struct X) == sizeof (int));
  assert (sizeof (struct X) == alignof (struct X) * 2);
  assert (alignof (struct X) == sizeof (int));
}

void
test_alignas (void)
{
  struct X
  {
    short s;
#if (MSVC)
#pragma warning(disable : 4324)
    char alignas (sizeof (int)) ss[sizeof (int)];
#else
    char alignas (alignof (int)) ss[sizeof (int)];
#endif
  };

  assert (sizeof (struct X) == sizeof (int) * 2);

  __attribute__ ((unused)) char alignas (2) c2 = 'A';
  __attribute__ ((unused)) char alignas (8) c8 = 'B';
  __attribute__ ((unused)) char alignas (int) c4 = 'C';

  assert ((size_t)&c2 % 2 == 0);
  assert ((size_t)&c8 % 8 == 0);
  assert ((size_t)&c4 % sizeof (int) == 0);

#define _m_(x, y) ((size_t) & (x)) == (((size_t) & (x)) / (y)) * (y)
  __attribute__ ((unused)) char alignas (double) c1 = 'A';
  assert (_m_ (c1, sizeof (double)));
#undef _m_
}

void
test_generic (void)
{
#if !(NM_HAVE_GENERIC)
  printf ("%s: no `generic' found\n", __FUNCTION__);
#else

#define _ndef_test_generic_(x)                                                \
  generic ((x), int : 1, double : 2, default : 'a')
  assert (1 == _ndef_test_generic_ (0) && "int");
  assert (2 == _ndef_test_generic_ (0.1) && "double");
  assert ('a' == _ndef_test_generic_ ("X") && "default");
#undef _ndef_test_generic_

#endif
}

void
test_str (void)
{
  assert (sizeof (_str_ (0600)) == 5);
}

void
test_cat (void)
{
  int _cat_ (a, 1) = 1;
  assert (a1 == 1);
}

void
test_isut (void)
{
  assert (_isut_ (unsigned short));
  const int is_unsigned_char = _isut_ (char);
  if (is_unsigned_char)
    {
      assert (_isut_ (char) == _isut_ (unsigned char));
    }
}

void
test_nof (void)
{
  int a[] = {
    1,
    2,
    3,
  };
  assert (_nof_ (a) == sizeof (a) / sizeof (*a));
}

void
test_swp (void)
{
  int i1 = 0x1122, i2 = 0x3344;
  _swp_ (&i1, &i2, sizeof (int));
  assert (0x1122 == i2 && 0x3344 == i1);

  int *p1 = &i1, *p2 = &i2;
  _swp_ (&p1, &p2, sizeof (int *));
  assert (0x1122 == *p1 && 0x3344 == *p2);

  char *s1 = "abcdef", *s2 = "12345";
  _swp_ (&s1, &s2, sizeof (char *));
  assert (strcmp ("abcdef", s2) == 0 && strcmp ("12345", s1) == 0);

  char sa1[] = "abcdef", sa2[] = "12345";
  char *ss1 = sa1, *ss2 = sa2;
  _swp_ (&ss1, &ss2, sizeof (char *));
  assert (strcmp ("abcdef", ss2) == 0 && strcmp ("12345", ss1) == 0);
}
