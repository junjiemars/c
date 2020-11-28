#include <_x86_.h>

void
simple_variables(void)
{
	int i;
	char c;

	i = 6;
	i++;
	c = 'A';
}

int
main(void)
{
	simple_variables();
}
