/**
 * Nore Unix standard
 */

#ifndef _NUSTD_H_
#define _NUSTD_H_


#include <nore.h>
#include <ncstd.h>


#if (WINNT)
#  include <windows.h>
#  include <process.h>
#else
#  if (DARWIN)
#    if !defined (_DARWIN_C_SOURCE)
#      define _DARWIN_C_SOURCE
#      include <sys/types.h>
#      undef _DARWIN_C_SOURCE
#    endif
#    include <unistd.h>
#  endif
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
