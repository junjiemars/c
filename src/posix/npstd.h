/**
 * Nore POSIX standard
 *
 * POSIX: https://pubs.opengroup.org/onlinepubs/9699919799/mindex.html
 *
 */

#ifndef _NPSTD_H_
#define _NPSTD_H_


#include <nore.h>



#if !defined(_POSIX_C_SOURCE)
#  define _POSIX_C_SOURCE  200809L
#endif



#if (DARWIN)
#  if !defined(_DARWIN_C_SOURCE)
#    define _DARWIN_C_SOURCE
#  endif
#endif


#if (LINUX)
#  if !defined(_GNU_C_SOURCE)
#    define _GNU_C_SOURCE
#  endif
#endif



#endif /* _NPSTD_H_ */
