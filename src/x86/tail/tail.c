#include "_x86_.h"

static int f(int);
static int g(int);

int
main(int argc, char *argv[])
{
  int  i  =  1, r;

  if (argc > 1)
    {
      i = atoi(argv[1]);
    }

  r = f(i);

  printf("i = %d\n", r);
}


int
f(int x)
{
  return g(x + 1);
}

int
g(int x)
{
  return x * 2;
}
