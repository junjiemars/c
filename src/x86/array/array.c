#include <_x86_.h>
#include <stdio.h>


void
offset()
{
	int i;
	int a[20];
	i = 19;
	a[i] = 0x11223344;
	i[a]++;
}

void 
array()
{
	int a[20];
	a[19] = 0x11223344;
}

void
structure()
{
	int i;
	struct binky a[20];
	i = 19;
	a[i].f = i;
}


int
main(int argc, const char *argv[])
{
	_unused_(argc);
	_unused_(argv);

	offset();
	array();

	printf("sizeof(struct binky)=%zu\n", sizeof(struct binky));
	structure();
}
