#include "scope.h"
#include "_lang_.h"

#if MSVC
/* warning C4702: unreachable code */
#pragma warning(disable : 4702)
#endif

/*
 * file scope
 */

/* declaration, definition with initializer  */
int i0 = 123;

/* declaration, tentative definition without initializer to 0 */
int i1;

/* extern declaration, must without initializer */
extern int i2;

/*
 * function `sub' forward declaration
 */
static void sub (int, int);
static void lab (int);

int
inc ()
{
  static int i = 0;
  return i++;
	/* `i' has function scope */
}

#if defined(MSVC)
int
map (int (*fn) (int n), int *a)
{
  for (int i0 = 0; i0 < 4; ++i0)
    {
      a[i0] = (*fn) (a[i0]);
    }
  return 4;
}
#else
int
map (int (*fn) (int n), int a[static 4])
{

  for (int i0 = 0; i0 < 4; ++i0)
    {
      a[i0] = (*fn) (a[i0]);
    }
  return 4;

  /*
   * file scope variable `i0' be shadowed by the file scope `i0'.
   */
}
#endif /* end of defined(MSVC) */

int
main (void)
{
  printf ("i0 = %i, i1 = %i, i2 = %i\n", i0, i1, i2);

  int a[] = { 1, 2, 3, 4 };
  map (&sqr, a);
  for (size_t i = 0; i < sizeof (a) / sizeof (*a); ++i)
    {
      printf ("%i ", a[i]);
    }
  putchar ('\n');

  sub (i0, i1);
  sub (i0 + 1, i1 + 2);

  lab (0);
  lab (1);
}

void
sub (int i0, int i1)
{
  printf ("@sub: i0 = %i, i1 = %i\n", i0, i1);

  /*
   * 1. well, function parameter `i0' has the entire function scope,
   * so u can't: redefined it such as `int i0 += 1';
   *
   * 2. file scope variable `i0' be shadowed this function scope.
   */
}

void
lab (int a)
{
  if (a == 0)
    {
      goto label_1;
    label_0:
      printf ("@lab: label_0 <- %d\n", a);
    }
  else if (a == 1)
    {
      goto label_0;

    label_1:
      printf ("@lab: label_1 <- %d\n", a);
    }
  /*
   * `label' has function scope.
   */
}
