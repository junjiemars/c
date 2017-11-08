#include <_x86_.h>

struct binky {
	int a;
	char b, c, d, e;
	short f;
};

void
structure() {
	struct binky x;
	
	x.e = 'A';
	x.f = x.a;
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	structure();
}
