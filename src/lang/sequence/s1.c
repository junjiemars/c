#include "../_lang_.h"

/*
 * sequence point
 */

static int a (void);
static int b (void);

static unsigned ua (void);
static unsigned ub (void);

static int x;
static unsigned ux;

int
main (void)
{
  int r;
  x = 0;
  r = a () + b ();
  assert ((r == 2 || r == 8) && "cannot guarantee the order of execution");

  ux = 0u;
  r = (ua () + 5u) + (ub () + 7u);
  assert ((r == 20 || r == 14) && "cannot guarantee the order of left association");

  x = 0;
  r = (a () + 5) + (b () + 7);
  assert (r == 20 && "guaranteed the order of left association ");
  return 0;
}

int
a (void)
{
  return x += 2;
}

int
b (void)
{
  return x *= 3;
}

unsigned
ua (void)
{
  return ux += 2;
}

unsigned
ub (void)
{
  return ux *= 3;
}
