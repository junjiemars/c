#ifndef _NSTR_H_
#define _NSTR_H_


#include <npstd.h>
#include <string.h>


#if (MSVC) && (NM_HAVE_STRDUP)
#  define strdup  _strdup
#endif  /* strdup */


#endif /* end of _NSTR_H_ */
