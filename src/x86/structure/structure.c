#include <_x86_.h>
#include <stdio.h>

void
structure() {
	struct binky x;
	x.a = 'A';
	x.e = 'E';
	x.d = 'D';
	x.f = x.a;
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("sizeof(struct binky)=%zu\n", sizeof(struct binky));
	structure();
}
