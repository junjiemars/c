#include <_lang_.h>


int
main(void)
{
	int    i    =  1, j=2;
	int   *pi   =  &i, *pj = &j;
	int  **ppi  =  &pi;

	*ppi = pj;

	printf("ppi@%p=%i\n", ppi, **ppi);
}
