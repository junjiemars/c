#include "_lang_.h"


int
main(void)
{
	int    i      =  1;
	int   *pi     =  &i;
	int  **ppi    =  &pi;
  int    ii[]   =  {0x11, 0x22, 0x33};
  int (*pii)[]  =  &ii;
  int   *iip[]  =  {&i};

  i += 0x10;

	printf("ppi@%p=%i, ii[1]=0x%x, iip[0]=0x%x\n",
         ppi, **ppi, (*pii)[1], *(iip[0]));
}
