#include <_cio_.h>
#include <stdio.h>
#include <nint.h>

/*
 * conversion specification:
 * %[*][fldwidth][lenmodifier]convtype
 *
 * A. the optional asterisk is used to suppress conversion
 *
 * B. field width: see fo.c
 *
 * C. length modifier:
 *
 * D. conversion type:
 *  1) d signed decimal, base 10
 *  2) i signed decimal, base determined by the format of input
 *  3) o unsigned octal (input optionally signed)
 *  4) u unsigned (input optionally signed)
 *  5) x unsigned hexadecimal (input optionally signed)
 *  6) a,A,e,E,f,F,g,G float-point number
 *  7) c (with l length modifier, wide character)
 *  8) s (with l length modifier, wide string)
 *  9) [ matches a sequence of listed character, ending with ]
 * 10) [^ matches all characters except the ones listed, ending with ]
 *
 */


static void in_types(void);
static void in_seq(void);


int
main(void)
{
  in_types();
  in_seq();

  return 0;
}

void
in_types(void)
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

  printf("\nin types\n------------\n");

  sscanf(ss, fmt, &c, &s, &i, &l, &f, &d, &ld);

  printf("%c(char) %hd(short) %d(int) %ld(long)\n"
         "%f(float) %lf(double) %Lf(long double)\n",
         c, s, i, l, f, d, ld);
}

void
in_seq(void)
{
  char *ss = "abc abd";
  char *fmt1 = "%[abc] %[abc]";
  char *fmt2 = "%[^ ]";
  char b1[16];
  char b2[16];

  printf("\nin sequence\n------------\n");

  sscanf(ss, fmt1, &b1, &b2);
  printf("%s %s (%s -> %s)\n", b1, b2, ss, fmt1);

  sscanf(ss, fmt2, &b2);
  printf("%s (abc abd -> %s)\n", b2, fmt2);

}
