#include "../_lang_.h"
#include <stdio.h>

typedef int (*op) (int n);

enum
{
  ADD1,
  SUB1
};

static int add1 (int);
static int sub1 (int);
static int fn1 (int, op);
static op fn2 (int);
static int recursive_factorial (int);
static inline int _iter_fact (int, int);
static int iterative_factorial (int);

int
main (void)
{
  int i1 = 0x11223344;

  printf ("fn1(add1:%d)=%d\n", i1, fn1 (i1, &add1));
  printf ("fn1(sub1:%d)=%d\n", i1, fn1 (i1, &sub1));

  printf ("fn2(ADD1:%d)=%d\n", i1, fn2 (ADD1) (i1));
  printf ("fn2(SUB1:%d)=%d\n", i1, fn2 (SUB1) (i1));

  int f1 = 10;
  printf ("recursive_factorial(%i)=%i\n", f1, recursive_factorial (f1));
  printf ("iterative_factorial(%i)=%i\n", f1, iterative_factorial (f1));
}

int
add1 (int n)
{
  return (n + 1);
}

int
sub1 (int n)
{
  return (n - 1);
}

int
fn1 (int n, op fn)
{
  return fn (n);
}

op
fn2 (int op)
{
  if (ADD1 == op)
    return &add1;
  if (SUB1 == op)
    return &sub1;
  return 0;
}

int
recursive_factorial (int n)
{
  if (n < 0)
    return 0;
  if (n < 2)
    {
      return 1;
    }
  else
    {
      return n * recursive_factorial (n - 1);
    }
}

int
_iter_fact (int n, int acc)
{
  if (n == 1)
    {
      return acc;
    }
  else
    {
      return _iter_fact (n - 1, n * acc);
    }
}

int
iterative_factorial (int n)
{
  if (n < 0)
    return 0;
  return _iter_fact (n, 1);
}
