#include <_stdio_.h>
#include <stdio.h>

int
main(void)
{
  char    c;
  int     i, h;
  long    l;
  float   f;
  double  d;

  int n = fscanf(stdin,
                 "%c, %i, 0x%x, %li, %f, %lf",
                 &c, &i, &h, &l, &f, &d);
  printf("scanned count: %d\n", n);
  printf("c=%c, i=%i, h=0x%x, li=%li, f=%f, lf=%lf\n",
         c, i, h, l, f, d);

  return 0;
}
