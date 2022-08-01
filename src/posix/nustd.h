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


#if (MSVC)
#  include <BaseTsd.h>
#  include <windows.h>
#  include <process.h>
#else
#  include <sys/types.h>
#  include <unistd.h>
#endif


#if !(NM_HAVE_SLEEP)
#  error "sleep no found"
#elif (MSVC)
#  define sleep(x)  Sleep((x) * 1000)
#endif  /* sleep */


#if !(NM_HAVE_GETPID)
#  error "getpid no found"
#elif (WINNT)
#  define getpid  _getpid
#endif  /* getpid */


#if !(NM_HAVE_SSIZE_T)
typedef long ssize_t;
#endif  /* ssize_t */



#endif /* _NUSTD_H_ */
