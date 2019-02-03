#include <_lang_.h>

static int *volatile x;

int
raw(int *i) {
	*i += 0x22;
	return *i;
}

int
foo(int *volatile i) {
	*i += 0x22;
	return *i;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	x = &argc;
	foo(x);
	
	return 0;
}
