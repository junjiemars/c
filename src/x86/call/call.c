#include "_x86_.h"
#include <stdlib.h>
#include <stdio.h>

static void  caller(void);
static int   adder(int, int);
static int   fact(int);
static int   sum(int, int, int, int, int, int, int, int, int);

static void  ptr_caller(void);
static void  ptr_callee_p(int *);
static void  ptr_callee_pp(int **);
static void  struct_caller(void);
static void  struct_callee(struct fraction);
static void  struct_callee2(struct fraction2);
static void  float_caller(void);
static void  float_callee(float);


int
main(void)
{
  caller();
  ptr_caller();
  struct_caller();
  float_caller();

}


static int
adder(int one, int two)
{
  int  sum;

  sum = one + two;
  return sum;
}

static void
caller(void)
{
  (void) adder(0x1100, 0x22);

  (void) fact(3);

  (void) sum(1, 2, 3, 4, 5, 6, 7, 8, 9);
}


static void
ptr_caller(void)
{
  int  i, ii, *pp;

  i = 0x1100;
  ptr_callee_p(&i);

  ii = 0x2200;
  pp = &ii;
  ptr_callee_pp(&pp);
}

static void
ptr_callee_p(int *p)
{
  *p += 1;
}

static void
ptr_callee_pp(int **pp)
{
  **pp += 1;
}


static void
struct_callee(struct fraction i)
{
  i.denominator = i.denominator + 1;
}

static void
struct_callee2(struct fraction2 m)
{
  m.denominator = m.denominator + 1;
}

static void
struct_caller(void)
{
  struct fraction small  =
    {
      0x11, 0x22
    };

  struct fraction2 medium  =
    {
      0x11L, 0x22L
    };

  struct_callee(small);
  struct_callee2(medium);
}

int
fact(int n)
{
  if (0 == n) return 1;
  return n * fact(n-1);
}


int
sum(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
  int  sum;

  sum = a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
  return sum;
}

void
float_caller(void)
{
  float  f1  =  3.1415;

  (void) float_callee(f1);
}

void
float_callee(float f)
{
  float  sum;

  sum += 0.00001;
  (void) sum;
}
