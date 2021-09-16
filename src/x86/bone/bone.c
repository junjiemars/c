#include <_x86_.h>

void B(void);
void C(void);

void A(void)
{
	int x;
	short y;
	_unused_(x);
	_unused_(y);

	B();
	C();
}

void B(void)
{
	long x, z;
	int y;
	_unused_(x);
	_unused_(y);
  _unused_(z);
	C();
}

void C(void)
{
	double x;
	long y;
	_unused_(x);
	_unused_(y);
}

int 
main(void)
{
	A();
}
