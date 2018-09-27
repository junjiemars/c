#include <_lang_.h>
#include <stdio.h>


/* duration: static */
int g_var_x = 0x11223344;


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\nstatic duration\n");
	printf("-----------------\n");
	printf("g_var_x = 0x%08x\n", g_var_x);
}
