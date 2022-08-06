#include "ncstd.h"
#include <stdio.h>

int
main(void)
{
#if defined(__STDC__)
  printf("%s=%i\n", _str_(__STDC__), (__STDC__+0));
#else
  printf("%s=(no symbol)\n", _str_(__STDC__));
#endif

#if defined(__STDC_VERSION__)
  printf("%s=%liL\n", _str_(__STDC_VERSION__), (__STDC_VERSION__+0L));
#else
  printf("%s=(no symbol)\n", _str_(__STDC_VERSION__));
#endif

  return 0;
}
