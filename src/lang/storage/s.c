#include <_lang_.h>
#include <stdio.h>


#if MSVC
 /* C4456: declaration of 'i' hides previous local declaration */
# pragma warning(disable:4456)
#endif


void
automatic_storage_class(void) {
	auto int x; /* garbage value */
#if GCC
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wuninitialized"
	printf("x = 0x%08x\n", x);
# pragma GCC diagnostic pop
#else
	_unused_(x);
#endif

	auto int i = 0x1122;
	{
		auto int i = 0x11223344;
		printf("inner i = 0x%08x\n", i++);
	}
	printf("outer i = 0x%08x\n", i++);
}


void
decay(char *a) {
	printf("a[0] = 0x%02x\n", a[0]);
}


void
register_storage_class(register int x) {
	register int i = x;
	printf("i = 0x%08x\n", i++);
	/* error: address of register variable requested */
	/* int *p = &i; */

	register char a[] = {0x11, 0x22, 0x33, 0x44, };
#if MSVC
	printf("a[0/%zu]\n", sizeof(a));
#elif CLANG || GCC
	printf("a[0/%zu] = 0x%02x\n", sizeof(a)/sizeof(a[0]), a[0]);
# if CLANG
	/* GCC error: address of register variable ‘a’ requested */
	decay(a);
# endif
#endif
}


void
static_storage_class(void) {
	static int i;
	{
		static int i = 0x11223344;
		printf("inner i = 0x%08x\n", i++);
	}
	printf("outer i = 0x%08x\n", i++);
}


void
external_storage_class(void) {
	extern int g_var_x;
	printf("g_var_x = 0x%08x\n", g_var_x++);
}


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\nautomatic storage class\n");
	printf("-------------------------\n");
	automatic_storage_class();
	automatic_storage_class();

	printf("\nregister storage class\n");
	printf("-----------------------\n");
	register_storage_class(0x11223344);

	printf("\nstatic storage class\n");
	printf("---------------------\n");
	static_storage_class();
	static_storage_class();
	static_storage_class();

	printf("\nexternal storage class\n");
	printf("------------------------\n");
	external_storage_class();
	external_storage_class();
}
