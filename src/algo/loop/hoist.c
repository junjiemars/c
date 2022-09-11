#include <_algo_.h>

/*
 * Loop Hoisting
 *
 */


#define N  5

static int hoist1(int);


int
main(void)
{
  hoist1(3);

  return 0;
}

int
hoist1(int x)
{
  int  t  =  0;
  int  a  =  x + 1;
  int  b  =  x * 2;
  int  i  =  0;

 L1:
  i += 1;

  t = a + b;                    /* can be hoisting outside the loop */

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
