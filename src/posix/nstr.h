#ifndef _NSTR_H_
#define _NSTR_H_


#include <npstd.h>
#include <string.h>


#if (NM_HAVE_STRDUP)
#  if (MSVC)
#    if defined(strdup)
#      undef  strdup
#    endif
#    define strdup  _strdup
#  endif
#endif  /* strdup */


#if (WINNT)
#  if !defined(strerror_r)
#    define strerror_r(e, b, s)  strerror_s((b), (s), (e))
#  endif
#endif  /* strerror_r */



#endif /* end of _NSTR_H_ */
