/**
 * Nore POSIX standard
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/mindex.html
 *
 */

#ifndef _NPSTD_H_
#define _NPSTD_H_


#include <nore.h>


#if (LINUX)
#  if defined(_POSIX_C_SOURCE)
#    undef _POSIX_C_SOURCE
#  endif
#  define _POSIX_C_SOURCE  200809L

#endif    /* LINUX */


#endif /* _NPSTD_H_ */
