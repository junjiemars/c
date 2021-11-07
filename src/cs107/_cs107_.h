#ifndef _CS107_H_
#define _CS107_H_

#include <nore.h>

/* #if (WINNT) */
/* #  include <windows.h> */
/* #  include <process.h> */
/* #  define getpid  GetCurrentProcessId */
/* #else */
/* #  include <sys/types.h> */
/* #  include <unistd.h> */
/* #endif */


#include <stddef.h>
#if (MSVC)
#  include <BaseTsd.h>
   typedef __int8            int8_t;
   typedef unsigned __int8   uint8_t;
   typedef __int16           int16_t;
   typedef unsigned __int16  uint16_t;
   typedef __int32           int32_t;
   typedef unsigned __int32  uint32_t;
   typedef __int64           int64_t;
   typedef unsigned __int64  uint64_t;
   typedef SSIZE_T           ssize_t;
#else
#  include <stdint.h>
#endif


#if (MSVC)
#pragma warning(disable:4244)
#pragma warning(disable:4996)
#else
#endif  /* MSVC */


#ifdef countof
#  undef countof
#endif
#define countof(a)  (sizeof(a)/sizeof(*(a)))


#define _unused_(x)  (void)(x)


#endif /* end of _CS107_H_ */
