#include <_lang_.h>
#include <stdio.h>


static void fn_auto();
static void fn_static();
static void fn_extern();


/* duration: static */
int g_var_x = 0x11223344;

int
main(void)
{

	printf("\nstatic duration\n");
	printf("-----------------\n");
	printf("g_var_x = 0x%08x\n", g_var_x);

	printf("\nautomatic duration\n");
	printf("--------------------\n");
	fn_auto();

	printf("\nstatic duration\n");
	printf("-----------------\n");
	fn_static();
	fn_static();

	printf("\nstatic duration\n");
	printf("-----------------\n");
	fn_extern();
	fn_extern();
}


void
fn_auto()
{
	int i = 0xaabbccdd;
	printf("auto i = 0x%08x in fn_auto()\n", i);
}

void
fn_static()
{
	static int static_i = 0x11223344;
	printf("static i = 0x%08x in fn_static()\n", static_i++);
}

void
fn_extern()
{
	extern int g_var_y;
	printf("g_var_y = 0x%08x in fn_extern()\n", g_var_y++);
}
