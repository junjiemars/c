#include "_x86_.h"

static int f1(int);
static int f2(int);
static int g1(int);
static int g2(int);

int
main(void)
{
  int  i;

  i = f1(1);
  i = f2(1);

  printf("i = %d\n", i);
}

int
f1(int x)
{
  return 1 + g1(x);
}

int
g1(int x)
{
  return x + 1;
}

int
f2(int x)
{
  return 1 + g2(x);
}

__attribute__((always_inline)) int
g2(int x)
{
  return x + 1;
}
