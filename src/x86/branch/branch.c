#include "_x86_.h"


void
branch()
{
	int  i;

	i = 1;

	if (i >= 0)
    {
      i *= 2;
    }

	i = 10;
}


int
main(void)
{
	branch();
}
