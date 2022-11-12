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

#if defined(NM_CLK_TCK)
  printf("%s=%li\n", _str_(NM_CLK_TCK), (long) (NM_CLK_TCK+0));
#else
  printf("%s=(no symbol)\n", _str_(NM_CLK_TCK));
#endif


  return 0;
}
