#include <_x86_.h>

void
simple_variables() {
	int i;
	char c;

	i = 6;
	i++;
	c = 'A';
}

int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	simple_variables();
}
