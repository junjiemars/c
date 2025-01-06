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


#if (MSVC)
#  if (NM_HAVE_SSIZE_T)
typedef SSIZE_T  ssize_t;
#  else
typedef long long  ssize_t;
#  endif
#endif  /* ssize_t */



#if (MSVC)
#  define sleep(x)  Sleep((x) * 1000)
#endif  /* sleep */


#if (MSVC)
#  define getpid  _getpid
#endif  /* getpid */


#if (NM_HAVE_GETTIMEOFDAY)
#  include <sys/time.h>
#  define _timed_(E, R)                                         \
do                                                              \
{                                                               \
  const long long m = 1000000;                                  \
  struct timeval s, e;                                          \
  gettimeofday(&s, NULL);                                       \
  (E);                                                          \
  gettimeofday(&e, NULL);                                       \
  R = ((e.tv_sec-s.tv_sec)*m+(e.tv_usec-s.tv_usec))/(double)m;  \
} while (0)
#else
#  include <time.h>
#  define _timed_(E, R)  _time_(E, R)
#endif  /* _timed_ */



#endif /* _NUSTD_H_ */
