#include "npstd.h"
#include <stdio.h>


int
main(void)
{

#if (_POSIX_C_SOURCE)
  printf("_POSIX_C_SOURCE=%luL\n", _POSIX_C_SOURCE);
#else
  printf("_POSIX_C_SOURCE=(no symbol)\n");


#endif

#if (__STDC_VERSION__)
  printf("__STDC_VERSION__=%luL\n", __STDC_VERSION__);
#else
  printf("__STDC_VERSION__=(no symbol)\n");

#endif
}
