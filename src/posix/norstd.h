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


#ifdef MSVC
char*
dirname(char *path) {
	static TCHAR d[PATH_MAX + 1], *b;
	if (0 == GetFullPathName(path, _countof(d), d, &b)) {
		return 0;
	}
	b[-1] = 0; /* remove '/basename' part */
	return d;
}
#endif /* MSVC */


#endif /* _NORSTD_H_ */
