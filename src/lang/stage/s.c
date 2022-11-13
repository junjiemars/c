#include "_lang_.h"

/*
 * 1. translation environment.
 * preprocessing translation unit -> translation unit -> C program.
 *
 * 2. execution environment.
 * hosted environment:
 * a) int main(void);
 * b) int main(int argc, char *argv[]);
 *
 */

#define _sum_(a, b)  ((a) + (b))

#define _PI_  3.1415926535E0L

#if (__STDC_VERSION__) >= 199901L
#  define _PI_C99_  0x1.921fb54442d18p+1L
#endif

extern char **environ;

int  g_x1  =  0x11223344;
int  g_x2;



int
main(void)
{
	static int  s_x3  =  0x44002211;
	int         i     =  1;
	int         a[]   =  { 1, 2, 3 };

	a[i] = (i + 4) * (2 + 6);
	g_x2 = a[i+1];

	printf("Hello, stage: 0x%x, env[0]: %s\n",
         a[i] + g_x1 + _sum_(g_x2, s_x3),
         environ[0]);

  printf("PI(decimal): %Lf\n", _PI_);

#if (__STDC_VERSION__) >= 199901L
  printf("PI(hexadecimal): %Lf\n", _PI_C99_);
#endif

	return 0;
}
