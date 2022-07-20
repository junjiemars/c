/**
 * Nore Unix standard
 */

#ifndef _NUSTD_H_
#define _NUSTD_H_


#include <nore.h>

#if (DARWIN)
#  if !defined(_DARWIN_C_SOURCE)
#    define _DARWIN_C_SOURCE
#  endif
#endif


#if (LINUX)
#  if !defined(_GNU_SOURCE)
#    define _GNU_SOURCE
#  endif
#endif


#include <npstd.h>
#include <ncstd.h>


#if (WINNT)
#  include <windows.h>
#  include <process.h>
#else
#  include <sys/types.h>
#  include <unistd.h>
#endif


#if !(NM_HAVE_SLEEP)
#  error "sleep no found"
#else
#  if (WINNT)
#    define sleep(x)  Sleep((x) * 1000)
#  endif
#endif  /* sleep */


#if !(NM_HAVE_GETPID)
#  error "getpid no found"
#else
#  if (WINNT)
#    define getpid  _getpid
#  endif
#endif  /* getpid */


#endif /* _NUSTD_H_ */
