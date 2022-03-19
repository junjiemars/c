#ifndef _NINT_H_
#define _NINT_H_

#include <nore.h>


#if !defined(NM_HAVE_STDINT_H)
#  error "<stdint.h> no found"
#endif


#include <stdint.h>


#if (MSVC)
#include <BaseTsd.h>
typedef INT8    int8_t;
typedef UINT8   uint8_t;
typedef INT16   int16_t;
typedef UINT16  uint16_t;
typedef INT32   int32_t;
typedef UINT32  uint32_t;
typedef INT64   int64_t;
typedef UINT64  uint64_t;
#endif


#if (NM_HAVE_SSIZE_T)
#  if (MSVC)
#    include <BaseTsd.h>
typedef SSIZE_T ssize_t
#  else
#    include <sys/types.h>
#  endif
#else
typedef long ssize_t
#endif


#endif /* end of _NINT_H_ */
