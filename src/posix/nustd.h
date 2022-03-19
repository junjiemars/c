/**
 * Nore Unix standard
 */

#ifndef _NUSTD_H_
#define _NUSTD_H_


#include <nore.h>
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
#  if (WINNT)
#    define sleep(x)  Sleep((x) * 1000)
#  endif
#endif  /* sleep */


#if !(NM_HAVE_GETPID)
#  error "getpid no found"
#  if (WINNT)
#    define getpid()  _getpid()
#  endif
#endif  /* getpid */


#endif /* _NUSTD_H_ */
