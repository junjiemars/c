#include "_x86_.h"

void B(void);
void C(void);

void A(void)
{
	int    x;
	short  y;

  (void) (x);
  (void) (y);
}

void B(void)
{
	long  x, z;
	int   y;

	(void) (x);
	(void) (y);
  (void) (z);

	C();
}

void C(void)
{
	double  x;
	long    y;

	(void) (x);
	(void) (y);
}

int
main(void)
{
	A();
  B();
}
