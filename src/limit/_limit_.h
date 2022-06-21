#ifndef _LIMIT_H_
#define _LIMIT_H_

#include <nore.h>

/* #include <nustd.h> */
/* #include <ncstd.h> */
/* #include <limits.h> */

#if defined(LINUX)
#  include <unistd.h>
#  include <limits.h>
#endif

#include <stdio.h>


#define FMT_S_L32(t)  "%-32s"t
#define FMT_S_R20     ": %24s\n"
#define FMT_I_RD      ": %24d\n"
#define FMT_I_RLD     ": %24ld\n"
#define FMT_I_RLLD    ": %24lld\n"
#define FMT_I_RU      ": %24u\n"
#define FMT_I_RLU     ": %24lu\n"
#define FMT_I_RLLU    ": %24llu\n"

#define S_NOSYM  "(no symbol)"



#endif /* end of _LIMIT_H_ */
