#include <_x86_.h>

void
foo() {
	int a;
	int b;
	b = 1;
	a = b + 2;	
	_unused_(a);
}

int 
main() {
	foo();
}
