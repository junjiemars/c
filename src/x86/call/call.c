#include <_x86_.h>
#include <stdio.h>

static int
adder(int one, int two) {
	int sum;
	sum = one + two;
	return sum;
}

static void
caller(void) {
	int n = 0x22;
	n = adder(n, 0x1100);
	n = 0x1f;
}

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	adder(0x1100, 0x22);
	caller();	
}
