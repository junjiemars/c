#ifndef _DEFS_H_
#define _DEFS_H_

#if !(NM_HAVE_RESTRICT)
#  if (NM_HAVE___RESTRICT)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif  /* NM_HAVE_RESTRICT */


#if !(NM_HAVE_STATIC_ASSERT)
#  ifdef static_assert
#    undef static_assert
#  endif
#  define static_assert(e, m) enum {static_assert = 1/!!((e) && (m))}
#endif  /* NM_HAVE_STATIC_ASSERT */


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


#endif /* end of _DEFS_H_ */
