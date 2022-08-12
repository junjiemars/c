#ifndef _NSTR_H_
#define _NSTR_H_


#include <npstd.h>
#include <string.h>


#if (NM_HAVE_STRDUP)
#  if (MSVC)
#    define strdup  _strdup
#  endif
#endif  /* strdup */


#endif /* end of _NSTR_H_ */
