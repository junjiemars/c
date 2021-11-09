#ifndef _CTL_H_
#define _CTL_H_

#include <nore.h>


#if (NDEBUG)
#  define ASSERT(x) ((void)(x))
#else
#  define ASSERT assert
#endif


#if (MSVC)
#pragma warning(disable:4127)
#endif

#define _unused_(x) ((void)(x))

#endif /* _CTL_H_ */
