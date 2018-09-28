#include <_lang_.h>
#include <stdio.h>

void
automatic_storage_class(void) {
	auto int x; /* garbage value */
#if GCC
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wuninitialized"
	printf("x = 0x%08x\n", x);
# pragma GCC diagnostic pop
#endif

	auto int i = 0x1122;
	{
		auto int i = 0x11223344;
		printf("inner i = 0x%08x\n", i);
	}
	printf("outer i = 0x%08x\n", i);
}

void
decay(short *a) {
	printf("a[0] = 0x%04x\n", a[0]);
}

void
register_storage_class(void) {
	register int i = 0x11223344;
	printf("i = 0x%08x\n", i);
	/* error: address of register variable requested */
	/* int *p = &i; */

	register char a[] = {0x11, 0x22, 0x33, 0x44, };
	printf("a[0/%zu] = 0x%02x\n", sizeof(a)/sizeof(a[0]), a[0]);
#if CLANG
	decay(a);
#else
	/* GCC error: address of register variable ‘a’ requested */
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


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\nautomatic storage class\n");
	printf("-------------------------\n");
	automatic_storage_class();

	printf("\nregister storage class\n");
	printf("-----------------------\n");
	register_storage_class();

	printf("\nstatic storage class\n");
	printf("---------------------\n");
	static_storage_class();
	static_storage_class();
	static_storage_class();
}
