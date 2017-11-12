#include <_x86_.h>


void 
array() {
	int a[20];
	a[19] = 7;
}

struct binky {
	int a;
	char b, c, d, e;
	short f;
};

void
structure() {
	int i;
	struct binky a[20];
	i = 3;
	a[i].f = i;
}


int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	array();
	structure();
}
