#include <nlim.h>
#include <stdio.h>


int
main(void)
{
#if defined(NM_LINE_MAX)
  printf("%s=%li\n", _str_(NM_LINE_MAX), (long) (NM_LINE_MAX+0));
#else
  printf("%s=(no symbol)\n", _str_(NM_LINE_MAX));
#endif

#if defined(NM_PAGE_SIZE)
  printf("%s=%li\n", _str_(NM_PAGE_SIZE), (long) (NM_PAGE_SIZE+0));
#else
  printf("%s=(no symbol)\n", _str_(NM_PAGE_SIZE));
#endif

#if defined(NM_GETPW_R_SIZE_MAX)
  printf("%s=%li\n", _str_(NM_GETPW_R_SIZE_MAX),
         (long) (NM_GETPW_R_SIZE_MAX+0));
#else
  printf("%s=(no symbol)\n", _str_(NM_GETPW_R_SIZE_MAX));
#endif

  return 0;
}
