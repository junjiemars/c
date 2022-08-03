#ifndef _NSTR_H_
#define _NSTR_H_


#include <npstd.h>

#if (MSVC)
#pragma warning(push)
#  pragma warning(disable:4996)
#  include <string.h>
#pragma warning(pop)
#else
#  include <string.h>
#endif


#if !(NM_HAVE_STRDUP)
#  error "strdup no found"
#else
#  if (MSVC)
#    define strdup  _strdup
#  endif
#endif  /* strdup */


#endif /* end of _NSTR_H_ */
