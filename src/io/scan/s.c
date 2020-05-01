#include <_io_.h>
#include <stdio.h>
 
int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  char c;
  int i, h;
  long l;
  float f;
  double d;
	
  int n = fscanf(stdin,
                 "%c, %i, 0x%x, %li, %f, %lf",
                 &c, &i, &h, &l, &f, &d);
  printf("scanned count: %d\n", n);
  printf("c=%c, i=%i, h=0x%x, li=%li, f=%f, lf=%lf\n",
         c, i, h, l, f, d);

  return 0;
}

