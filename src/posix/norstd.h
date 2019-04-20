/*
 * Nore Standard Header (https://github.com/junjiemars/nore)
 */

#ifndef _NORSTD_H_
#define _NORSTD_H_


#if WINNT
#  include <windows.h>
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
#elif NM_HAVE_UNISTD_H
#  include <unistd.h>
#else
#  error cannot find unistd.h
#endif


#endif /* _NORSTD_H_ */
