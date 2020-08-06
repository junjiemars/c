#ifndef _INTS_H_
#define _INTS_H_

#if defined(NM_HAVE_INTTYPES_H)
# include <inttypes.h>
#endif /* end of NM_HAVE_INTTYPES_H */

#if defined(NM_HAVE_STDINT_H)
# include <stdint.h>
#else
# include <stddef.h>
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif /* end of NM_HAVE_STDINT_H */

#if (MSVC)
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#define timegm _mkgmtime
#else
#  include <sys/types.h>
#endif
#endif /* end of _INTS_H_ */
