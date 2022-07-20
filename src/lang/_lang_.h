#ifndef _LANG_H_
#define _LANG_H_

#include <npstd.h>
#include <ncstd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* #if (GCC) */
/* #  if defined(_GNU_SOURCE) */
/* #    undef _GNU_SOURCE */
/* #  endif  /\* _GNU_SOURCE *\/ */
/* # */
/* #  if defined(_POSIX_C_SOURCE) */
/* #    undef _POSIX_C_SOURCE */
/* #  endif  /\* _POSIX_C_SOURCE *\/ */
/* #  define _POSIX_C_SOURCE 200809L */
/* # */
/* #  if !defined(_DEFAULT_SOURCE) */
/* #    define _DEFAULT_SOURCE */
/* #  endif */
/* #endif  /\* GCC *\/ */


#if (MSVC)
/* warning C4996: 'strncpy': This function or variable may be
	 unsafe. Consider using strcpy_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS. */
#  pragma warning(disable : 4996)
#endif  /* end of MSVC */


/* #ifdef NM_HAVE_STDINT_H */
/* # include <stdint.h> */
/* #else */
/* # include <stddef.h> */
/* typedef __int8 int8_t; */
/* typedef unsigned __int8 uint8_t; */
/* typedef __int16 int16_t; */
/* typedef unsigned __int16 uint16_t; */
/* typedef __int32 int32_t; */
/* typedef unsigned __int32 uint32_t; */
/* typedef __int64 int64_t; */
/* typedef unsigned __int64 uint64_t; */
/* #endif /\* end of NM_HAVE_STDINT_H *\/ */


/* #if (NM_HAVE_TYPEOF) */
/* #  if (CLANG) */
/* #    define typeof __typeof__ */
/* #  elif (GCC) */
/* #    define typeof __typeof__ */
/* #  elif (MSVC) */
/* #    define typeof decltype */
/* #  endif */
/* #endif  /\* NM_HAVE_TYPEOF *\/ */


#if (WINNT) && (MSVC)
#  define strerror_r(errno, buf, len) strerror_s(buf, len, errno)
#  define strtok_r                    strtok_s
#  define strdup                      _strdup
#endif


/* #if (NDEBUG) */
/* #  define ASSERT(x) ((void)(x)) */
/* #else */
/* #  define ASSERT assert */
/* #endif */


/* #define _unused_(x) ((void)(x)) */

#endif /* _LANG_H_ */
