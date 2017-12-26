#include <_x86_.h>
#include <stdio.h>

void
structure() {
	struct binky x;
	x.a = 0x22334441;
	x.b = 'B';
	x.c = 'C';
	x.d = 'D';
	x.e = 'E';
	x.f = x.a;
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("sizeof(struct binky)=%zu\n", sizeof(struct binky));
	structure();
}
