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
 * C. length modifier: see fo.c
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
 * 11) p point to a void
 * 12) n point to a signed integer into which is writen the number of character
 *     read so far
 * 13) % a % sign
 *
 */


static void in_convtype(void);
static void in_convtype_n(void);
static void in_convtype_match(void);


int
main(void)
{
  in_convtype();
  in_convtype_n();

  in_convtype_match();

  return 0;
}

void
in_convtype(void)
{
  char *ss = "a 123 1234 12345 3.1 3.14 3.141 12345";
  char *fmt = "%c %hi %d %ld %f %lf %Lf %p";

  char c;
  short s;
  int i;
  long l;
  float f;
  double d;
  long double ld;
  int *p;

  printf("\nin conversion type\n------------\n");

  sscanf(ss, fmt, &c, &s, &i, &l, &f, &d, &ld, &p);

  printf("%c (char)\n"
         "%hd (short)\n"
         "%d (int)\n"
         "%ld (long)\n"
         "%f (float)\n"
         "%lf (double)\n"
         "%Lf (long double)\n"
         "%p (p)\n",
         c, s, i, l, f, d, ld, p);

}

void
in_convtype_n(void)
{
  int n;

  printf("\nin conversion type: n\n------------\n");

  printf("%d, %s%n", 12345, "abc", &n);
  printf(" (n = %d)\n", n);
}

void
in_convtype_match(void)
{
  char *ss = "123 abc def";
  char *fmt1 = "%3[^abc] %3[abc] %3s";
  char b1[16] = {0};
  char b2[16] = {0};
  char b3[16] = {0};

  printf("\nin match\n------------\n");

  sscanf(ss, fmt1, &b1, &b2, &b3);

  printf("%s %s %s (%s -> %s)\n", b1, b2, b3, ss, fmt1);
}
