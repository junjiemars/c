#include "_limit_.h"
#include <limits.h>

int
main(void)
{
#if defined(_POSIX_ARG_MAX)
  pr_limit(_str_(_POSIX_ARG_MAX), _POSIX_ARG_MAX);
#else
  pr_limit_no(_str_(_POSIX_ARG_MAX));

#endif  /* _POSIX_ARG_MAX */

#if defined(_POSIX_CHILD_MAX)
  pr_limit(_str_(_POSIX_CHILD_MAX), _POSIX_CHILD_MAX);
#else
  pr_limit_no(_str_(_POSIX_CHILD_MAX));

#endif  /* _POSIX_CHILD_MAX */

  return 0;
}
