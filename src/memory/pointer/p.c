#include <_memory_.h>
#include <stdio.h>



void void_ptr() {
	int x = 0x1122;
	void* p = (void*)&x;
	int* y = p;

	printf("sizeof(void*) = %"PRIu32"\n", NM_HAVE_SIZEOF_VOID_POINTER);
	printf("(void*) = %p, (int*) = %p, (int*) = %p\n", p, &x, y);
}


int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\nSIGNED LEFT SHIFT\n");
	printf("----------\n");
	void_ptr();
}
