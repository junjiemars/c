#include <nlim.h>
#include <stdio.h>

static void  test_times(void);


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

  test_times();


  return 0;
}

void
test_times(void)
{
#if defined(_times_)
  CLK_TCK;
  double clock, user, sys;

  _times_(sleep(1), clock, user, sys);

  printf("_times_: real(%.2f), user(%.2f), sys:(%.2f)\n",
         clock, user, sys);

#endif
}
