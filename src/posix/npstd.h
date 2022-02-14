/**
 * Nore POSIX standard
 */

#ifndef _NPSTD_H_
#define _NPSTD_H_


#include <nore.h>


#if (LINUX)
#  if !defined(_GNU_SOURCE)
#    define _GNU_SOURCE
#  endif

#endif    /* LINUX */


#endif /* _NPSTD_H_ */
