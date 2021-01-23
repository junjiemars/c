#ifndef _PARALLEL_H_
#define _PARALLEL_H_

#include <nore.h>

#if (DARWIN) || (LINUX)
#  include <unistd.h>
#elif (WINNT)
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#endif

#define _unused_(x) ((void)(x))

#endif /* end of _PARALLEL_H_ */
