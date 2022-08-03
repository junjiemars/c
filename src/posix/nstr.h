#ifndef _NSTR_H_
#define _NSTR_H_


#include <npstd.h>
#include <string.h>

#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if !(NM_HAVE_STRDUP)
#  error "strdup no found"
#else
#  if (MSVC)
#    define strdup  _strdup
#  endif
#endif  /* strdup */


#endif /* end of _NSTR_H_ */
