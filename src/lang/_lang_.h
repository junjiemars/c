#ifndef _LANG_H_
#define _LANG_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#if MSVC
/* warning C4996: 'strncpy': This function or variable may be
	 unsafe. Consider using strcpy_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS. */
#  pragma warning(disable : 4996)
#endif



#endif /* _LANG_H_ */
