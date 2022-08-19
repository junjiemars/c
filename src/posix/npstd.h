/**
 * Nore POSIX standard
 *
 * POSIX:
 * https://pubs.opengroup.org/onlinepubs/9699919799/mindex.html
 *
 * XSI:
 * https://unix.org/version4/overview.html
 *
 */

#ifndef _NPSTD_H_
#define _NPSTD_H_


#include <nore.h>

#if defined(_POSIX_C_SOURCE)
#  undef _POSIX_C_SOURCE
#endif

#if (LINUX)
#  define _POSIX_C_SOURCE  200809L
#endif


#endif /* _NPSTD_H_ */
