/**
 * Nore POSIX standard
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
