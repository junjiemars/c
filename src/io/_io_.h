#ifndef _IO_H_
#define _IO_H_

#include <nore.h>
#include <stdio.h>

/* mmap */
#if DARWIN
#  include <fcntl.h>
#  include <unistd.h>
#  include <sys/mman.h>
#elif LINUX
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#  ifndef __USE_MISC
#    define __USE_MISC 1
#  endif
#  include <sys/mman.h>
#endif

#define _unused_(x) (void)(x)

#if MSVC
#  pragma warning(disable:4996) /* _CRT_SECURE_NO_WARNINGS  */
#endif

#if CLANG
#  pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

#if GCC
#  pragma GCC diagnostic ignored "-Wdeprecated-declarations"
/* #  include <features.h> */
#endif

void hex_out(const char *ss);

#endif /* end of _IO_H_ */
