#include <_x86_.h>
#include <stdlib.h>
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

static void
ptr_callee_p(int *p) {
	*p += 0x1100;
}

static void
ptr_caller_p(void) {
	int i;
	i = 0x22;
	ptr_callee_p(&i);	
	i += 1;
}

static void
ptr_callee_pp(int **pp) {
	*pp = malloc(sizeof(int*));
	**pp = 0x1133;
}

static void
ptr_caller_pp(void) {
	int i;
	int *p;

	i = 0x22;
	p = &i;
	ptr_callee_pp(&p);		
	*p += 0x1;
	free(p);
}

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	adder(0x1100, 0x22);
	caller();	

	ptr_caller_p();
	ptr_caller_pp();
}
