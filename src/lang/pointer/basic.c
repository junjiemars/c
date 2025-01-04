#include "../_lang_.h"

#if (MSVC)
#pragma warning(disable: 4048)
#endif

int
main (void)
{
  int i = 1;
  int *pi = &i;
  int **ppi = &pi;
  int ii[] = { 0x11, 0x22, 0x33 };
  int (*pii)[] = &ii;
  int *iip[] = { &i };

  i += 0x10;

  printf ("pi@%p=%i, ppi@%p=%i, ii[1]=0x%x, iip[0]=0x%x\n", pi, *pi, ppi,
          **ppi, (*pii)[1], *(iip[0]));
}
