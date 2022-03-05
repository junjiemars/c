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


#if (WINNT) && (NM_HAVE_SLEEP)
#  if !defined(sleep)
#    define sleep(x) Sleep((x) * 1000)
#  endif
#endif  /* sleep */


#if (WINNT) && (NM_HAVE_GETPID)
#  if !defined(getpid)
#    define getpid() _getpid()
#  endif
#endif  /* getpid */


#endif /* _NUSTD_H_ */
