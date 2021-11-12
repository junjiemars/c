#ifndef _IOSS_H_
#define _IOSS_H_


#include <nore.h>


#if (MSVC)
#  pragma warning(disable:4996)
#endif  /* _CRT_SECURE_NO_WARNINGS */


#if (LINUX)
#  if !defined(__USE_POSIX)
#    define __USE_POSIX
#  endif
#endif  /* LINUX */


#include <stdio.h>


#endif /* end of _IOSS_H_ */
