#include <_cio_.h>
#include <stdio.h>
#include <nint.h>

/*
 * conversion specification:
 * %[*][fldwidth][lenmodifier]convtype
 *
 * B. field width: see fo.c
 *
 * C. len modifier:
 *
 * D. convert type:
 *
 */


static void fmt_types(void);


int
main(void)
{
  fmt_types();

  return 0;
}

void
fmt_types(void)
{
  char *ss = "a 123 1234 12345 3.1 3.14 3.141";
  char *fmt = "%c %hi %d %ld %f %lf %Lf";

  char c;
  short s;
  int i;
  long l;
  float f;
  double d;
  long double ld;

  printf("\nformat types\n------------\n");

  sscanf(ss, fmt, &c, &s, &i, &l, &f, &d, &ld);

  printf("%c(char) %hd(short) %d(int) %ld(long)\n"
         "%f(float) %lf(double) %Lf(long double)\n",
         c, s, i, l, f, d, ld);
}
