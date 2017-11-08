#include <_x86_.h>
#include <stdlib.h>


void 
branch() {
	int i;
	i = 1;
	if (i >= 0)
		i *= 2;
	i = 10;
}


int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	branch();
}
