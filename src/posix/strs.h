#ifndef _STRS_H_
#define _STRS_H_


#if (GCC)
#  if defined(_GNU_SOURCE)
#    undef _GNU_SOURCE
#  endif  /* _GNU_SOURCE */
#
#  if defined(_POSIX_C_SOURCE)
#    undef _POSIX_C_SOURCE
#  endif  /* _POSIX_C_SOURCE */
#  define _POSIX_C_SOURCE 200809L
#
#  if !defined(_DEFAULT_SOURCE)
#    define _DEFAULT_SOURCE
#  endif
#endif  /* GCC */


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if (MSVC)
#  define strdup _strdup
#endif  /* strdup */

#include <string.h>


#endif /* end of _STRS_H_ */

