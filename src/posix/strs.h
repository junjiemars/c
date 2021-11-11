#ifndef _STRS_H_
#define _STRS_H_


#if (LINUX)
#  if !defined(__USE_POSIX)
#     define __USE_POSIX
#  endif
#endif

#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if (MSVC)
#  define strdup _strdup
#endif  /* strdup */

#include <string.h>


#endif /* end of _STRS_H_ */

