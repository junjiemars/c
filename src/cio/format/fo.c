#include <_cio_.h>
#include <stdio.h>
#include <nint.h>


/*
 * conversion specification:
 * %[flags][fldwidth][precision][lenmodifier]convtype
 *
 * A. flags:
 * 1) - left justify the output of field
 * 2) + always display sign of a signed conversion
 * 3)   (space) prefix a space if no sign is generated
 * 4) # convert using alternate form
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
 * D. len modifier
 * 1) hh signed or unsigned char
 * 2) h signed or unsigned short
 * 3) l signed or unsigned long
 * 4) ll signed or unsigned long long
 * 5) j intmax_t or uintmax_t
 * 6) z size_t
 * 7) t ptrdiff_t
 * 8) L long double
 *
 * E. convert type
 * 1) d,i signed deciaml
 * 2) o unsigned octal
 * 3) x,X unsigned hexaidicmal
 * 4) f double float-point number
 * 5) e,E double float-point in exponential format
 * 6) g,G interpreted as f,F,e, or E, depending on value converted
 * 7) a,A double float-point in hexadecimal expoential format
 * 8) c,C (lc) character
 * 9) s,S (ls) string
 * 10) P point to void
 * %) a % character
 *
 */

static void fmt_flags(void);
static void fmt_fldwidth(void);
static void fmt_lenmodifier(void);
static void fmt_convtype(void);


int
main(void)
{
  fmt_flags();
  fmt_fldwidth();
  fmt_lenmodifier();
  fmt_convtype();

  return 0;

}

void
fmt_flags()
{
  printf("\nformat flags\n------------\n");

  printf("%s\n", "abc");
  printf("%-s\n", "abc");

  printf("%d\n", 12345);
  printf("%-d\n", 12345);

  printf("%+d\n", 12345);
  printf("% d\n", 12345);

  printf("%#o\n", 12345);
  printf("%#x\n", 12345);

  printf("%0d\n", 12345);
}


void
fmt_fldwidth(void)
{
  printf("\nformat field width\n------------\n");

  printf("%10s%s\n", "abc", "|");
  printf("%-10s%s\n", "abc", "|");

  printf("%010d%s\n", 12345, "|");

}

void
fmt_lenmodifier(void)
{
  printf("\nformat len modifier\n------------\n");

  printf("%hd\n", (short) 12345);
  printf("%ld\n", 12345L);
  printf("%lld\n", 12345LL);
  printf("%jd\n", INTMAX_MAX);
  printf("%zd\n", sizeof(int));
  printf("%+td\n", (int *) &main - (int *) &fmt_lenmodifier);
  printf("%Lf\n", 12345.0L);


}

void
fmt_convtype(void)
{
  printf("\nformat convert type\n------------\n");

  printf("%e\n", 12345.0);
  printf("%E\n", 12345.0);

  printf("%g\n", 12345.0);
  printf("%G\n", 12345.0);

  printf("%a\n", 12345.0);
  printf("%A\n", 12345.0);

  printf("%c\n", 'a');
  printf("%C\n", 0x3bb);
  printf("%lc\n", 0x3bb);


  printf("%s\n", "abc");
  printf("%S\n", L"λ");
  printf("%ls\n", L"λ");

  printf("%p\n", &main);

  int n = 12345;
  printf("%n\n", &n);

  printf("%%\n");

}
