#ifndef _DS_H_
#define _DS_H_

#include "nore.h"

#ifdef MSVC
#pragma warning(disable:4996) /*_CRT_SECURE_NO_WARNINGS*/
#endif

#if NDEBUG
#  define ASSERT(x) ((void)(x))
#else
#  define ASSERT assert
#endif  /* end of NDEBUG */


#define _unused_(x) ((void)(x))

#endif  /* end of _DS_H_ */
