#include <x86.h>

int
foo() {
	int a;
	int b;
	b = 1;
	a = b + 2;	
	return a;
}

int 
main() {
	return foo();
}
