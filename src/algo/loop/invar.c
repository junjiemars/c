#include <_algo_.h>

/*
 * Loop Invariant:
 * can be outside the loop.
 *
 */


#define N  5

static int invar1(int);

int
main(void)
{
  invar1(5);

  return 0;
}

int
invar1(int x)
{
  int t = 0;
  int i = 0;
  int a = x;
  int b;

 L1:
  i += 1;
  b = 7;
  t = a + b;                    /* loop invariant */

  if (i < N)
    {
      goto L1;
    }
  else
    {
      goto L2;
    }

 L2:
  x = t;
  return x;
}
