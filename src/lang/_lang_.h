#ifndef _LANG_H_
#define _LANG_H_

#include <ncstd.h>
#include <nasrt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <assert.h>



#if (MSVC)
/* warning C4996: 'strncpy': This function or variable may be
	 unsafe. Consider using strcpy_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS. */
#  pragma warning(disable : 4996)
#endif  /* end of MSVC */



#if (WINNT) && (MSVC)
#  define strerror_r(errno, buf, len) strerror_s(buf, len, errno)
#  define strtok_r                    strtok_s
#  define strdup                      _strdup
#endif


#endif /* _LANG_H_ */
