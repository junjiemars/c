/**
 * Nore XSI standard
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/
 *
 */

#ifndef _XSTD_H_
#define _XSTD_H_


#include <nore.h>


#if (LINUX)
#  if defined(_XOPEN_SOURCE)
#    undef _XOPEN_SOURCE
#  endif
#  define _XOPEN_SOURCE  700

#endif    /* LINUX */


#endif /* _XSTD_H_ */
