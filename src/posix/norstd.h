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
#else
#  include <unistd.h>
#endif

#ifdef MSVC
#  include <windows.h>
#  include <tchar.h>
#  define PATH_MAX MAX_PATH
#else
#  ifdef LINUX
#    include <linux/limits.h>
#  else
#    include <limits.h>
#  endif
#  include <libgen.h>
#endif




#endif /* _NORSTD_H_ */
