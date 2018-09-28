#include <_lang_.h>
#include <stdio.h>

/* external linkage */
extern int g_var_x;
extern const int g_const_x;

/* internal linkage */
static int f_var_y = 0xaabbccdd;

void
foo(void) {
	int b_var_z = 0xa1b2c3d4;
	printf("b_var_z = 0x%08x\n", b_var_z);
}


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	printf("\nexternal linkage\n");
	printf("------------------\n");
	printf("g_var_x = 0x%08x\n", g_var_x);
	printf("g_const_x = 0x%08x\n", g_const_x);

	printf("\ninternal linkage\n");
	printf("------------------\n");
	printf("f_var_y = 0x%08x\n", f_var_y);

	printf("\nno linkage\n");
	printf("------------\n");
	foo();
}
