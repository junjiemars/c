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


#if (WINNT && NM_HAVE_STRERROR_R)
#  if defined(strerror_r)
#    undef  strerror_r
#  endif
#  define strerror_r(e, b, s)  ((int) strerror_s((b), (s), (e)))
#endif  /* strerror_r */



#endif /* end of _NSTR_H_ */
