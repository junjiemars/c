#include "_x86_.h"
#include <stdio.h>

void
structure()
{
  struct binky x;
  x.a = 0x22334411;
  x.b = 'B';
  x.c = 'C';
  x.d = 'D';
  x.e = 'E';
  x.f = x.a;
}

void
layered()
{
  struct binky x;
  struct fraction y;
  x.f = 0x3344;
  y.denominator = 0x1122;
}

int
main(void)
{
  printf("sizeof(struct binky)=%zu\n", sizeof(struct binky));
  structure();
  layered();
}
