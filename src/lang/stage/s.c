#include <_lang_.h>

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

	printf("Hello, stage: %d\n, env[0]: %s",
         a[i] + g_x1 + g_x2 + s_x3,
         environ[0]);

	return 0;
}
