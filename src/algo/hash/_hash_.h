#ifndef _HASH__H_
#define _HASH__H_

/*
 * http://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html
 *
*/

#include "_algo_.h"

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


unsigned long hash(const char *ss);

void print_hash(const char *name, const char *ss, unsigned long hash);

#endif /* end of _HASH__H_ */
