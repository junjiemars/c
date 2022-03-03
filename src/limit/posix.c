#include "_limit_.h"
#include <limits.h>

int
main(void)
{
#if defined(_POSIX_ARG_MAX)
  printf(FMT_S_L32(FMT_I_RD), _str_(_POSIX_ARG_MAX), _POSIX_ARG_MAX);
#else
  printf(FMT_S_L32(FMT_S_R20), _str_(_POSIX_ARG_MAX), S_NOSYM);

#endif  /* _POSIX_ARG_MAX */

#if defined(_POSIX_CHILD_MAX)
  printf(FMT_S_L32(FMT_I_RD), _str_(_POSIX_CHILD_MAX), _POSIX_CHILD_MAX);
#else
  printf(FMT_S_L32(FMT_S_R20), _str_(_POSIX_CHILD_MAX), S_NOSYM);

#endif  /* _POSIX_CHILD_MAX */

  return 0;
}
