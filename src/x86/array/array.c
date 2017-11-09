#include <_x86_.h>


void 
array() {
	int a[20];
	a[19] = 7;
}

int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	array();
}
