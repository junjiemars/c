#include <_cio_.h>
#include <nint.h>


/*
 * conversion specification:
 * %[flags][fldwidth][precision][lenmodifier]convtype
 *
 * A. flags:
 * 1) - left justify the output of field
 * 2) + always display sign of a signed conversion
 * 3) # convert using alternate form
 * 4)   (space) prefix a space if no sign is generated
 * 5) 0 prefix with leading zeros instead of padding with spaces
 *
 * B. field width:
 * 1) can be * (asterisk)
 * 2) an integer
 *
 * C. precision:
 * 1) can be * (asterisk)
 * 2) an integer
 *
 * D. length modifier
 * 1) hh signed or unsigned char
 * 2) h signed or unsigned short
 * 3) l signed or unsigned long
 * 4) ll signed or unsigned long long
 * 5) j intmax_t or uintmax_t
 * 6) z size_t
 * 7) t ptrdiff_t
 * 8) L long double
 *
 * E. conversion type
 *  1) d,i signed deciaml
 *  2) o unsigned octal
 *  3) u unsigned decimal
 *  4) x,X unsigned hexaidicmal
 *  5) f double float-point number
 *  6) e,E double float-point in exponential format
 *  7) g,G interpreted as f,F,e, or E, depending on value converted
 *  8) a,A double float-point in hexadecimal exponential format
 *  9) c,C (lc) character
 * 10) s,S (ls) string
 * 11) p point to a void
 * 12) n point to a signed integer into which is writen the number of character
 *     read so far
 * 13) % a % character
 *
 */

static void out_flags(void);
static void out_fldwidth(void);
static void out_precision(void);
static void out_lenmodifier(void);
static void out_convtype(void);
static void out_convtype_lc(void);
static void out_convtype_n(void);

int
main(void)
{
  out_convtype();
  out_flags();
  out_fldwidth();
  out_precision();
  out_lenmodifier();

  out_convtype_lc();
  out_convtype_n();

  return 0;

}

void
out_convtype(void)
{
  printf("\nout conversion type\n------------\n");

  printf("%c (char)\n"
         "%d (int)\n"
         "%i (int)\n"
         "%o (octal)\n"
         "%u (unsigned)\n"
         "%x (hex)\n",
         'a', 123, 12345, 12345, 12345, 12345);

  printf("%f (float)\n"
         "%e (float e)\n"
         "%g (float g)\n"
         "%a (double hex exponential)\n",
         123.456, 123.456, 123456.789, 123.456);

  printf("%s (string)\n", "abc");

  printf("%p (p)\n", (int *) &main);

}


void
out_flags()
{
  printf("\nout flags\n------------\n");

  printf("%s\n", "abc");
  printf("%-s (-)\n", "abc");

  printf("%d\n", 12345);
  printf("%-d (-)\n", 12345);

  printf("%+d (+)\n", 12345);
  printf("% d ( )\n", 12345);

  printf("%#o (#o)\n", 12345);
  printf("%#x (#x)\n", 12345);

  printf("%0d (0)\n", 12345);

}


void
out_fldwidth(void)
{
  printf("\nout field width\n------------\n");

  printf("%-10d| (-10)\n", 12345);
  printf("% 10d| ( 10)\n", 12345);
  printf("%010d| (010)\n", 12345);

}

void
out_precision(void)
{
  printf("\nout precision\n------------\n");

  printf("%.2f (.2f)\n", 123.456789);
  printf("%010.2f (010.2f)\n", 123.456789);

}

void
out_lenmodifier(void)
{
  printf("\nout length modifier\n------------\n");

  printf("%hd (hd)\n", (short) 12345);
  printf("%ld (ld)\n", 12345L);
  printf("%lld (lld)\n", 12345LL);
  printf("%jd (jd)\n", INTMAX_MAX);
  printf("%zd (zd)\n", sizeof(int));
  printf("%td (td)\n", (int *) &main - (int *) &out_lenmodifier);
  printf("%Lf (Lf)\n", 12345.6789L);


}

void
out_convtype_lc(void)
{
  printf("\nout wide character\n------------\n");

  printf("%lc (c)\n", L'λ');
  printf("%ls (ls)\n", L"中文");
}

void
out_convtype_n(void)
{
  int n;

  printf("\nout conversion type: n\n------------%n\n", &n);
  printf("(n = %d)\n", n);

  printf("%d, %s%n", 12345, "abc", &n);
  printf(" (n = %d)\n", n);
}
