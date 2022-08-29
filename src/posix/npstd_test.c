#include "npstd.h"
#include <stdio.h>


int
main(void)
{

#if (_POSIX_C_SOURCE)
  printf("_POSIX_C_SOURCE=%luL\n", (unsigned long) _POSIX_C_SOURCE);
#else
  printf("_POSIX_C_SOURCE=(no symbol)\n");

#endif


#if (__STDC_HOSTED__)
  printf("__STDC_HOSTED__=%i\n", (int) __STDC_HOSTED__);
#else
  printf("__STDC_HOSTED__=(no symbol)\n");

#endif


#if (__STDC_VERSION__)
  printf("__STDC_VERSION__=%luL\n", (unsigned long) __STDC_VERSION__);
#else
  printf("__STDC_VERSION__=(no symbol)\n");

#endif
}
