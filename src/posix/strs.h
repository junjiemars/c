#ifndef _STRS_H_
#define _STRS_H_


#include <nore.h>


#if (LINUX)
#  if !defined(__USE_XOPEN_EXTENDED)
#    define __USE_XOPEN_EXTENDED
#  endif  /* __USE_XOPEN_EXTENDED */
#endif  /* LINUX */


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if (MSVC)
#  define strdup _strdup
#endif  /* strdup */


#include <string.h>




#endif /* end of _STRS_H_ */

