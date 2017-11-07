#include <_x86_.h>

void B();
void C();

void A() {
	int x;
	short y;
	_unused_(x);
	_unused_(y);

	B();
	C();
}

void B() {
	long x;
	int y;
	_unused_(x);
	_unused_(y);
	C();
}

void C() {
	double x;
	long y;
	_unused_(x);
	_unused_(y);
}

int 
main() {
	A();
}
