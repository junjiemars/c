#ifndef _NLIM_H_
#define _NLIM_H_


#include <nustd.h>
#include <limits.h>


#if (MSVC)
#  if !defined(SSIZE_MAX)
#    define SSIZE_MAX  LONG_MAX
#  endif
#endif  /* SSIZE_MAX */


#endif /* end of _NLIM_H_ */
