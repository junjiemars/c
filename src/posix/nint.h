#ifndef _NINT_H_
#define _NINT_H_

#include <nore.h>


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
#  include <sys/types.h>
#endif


#endif /* end of _NINT_H_ */
