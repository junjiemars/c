/*
 * Nore Standard Header (https://github.com/junjiemars/nore)
 */

#ifndef _NORSTD_H_
#define _NORSTD_H_


#include <nore.h>


#if defined(GCC)
#  ifndef _GNU_SOURCE
#    define _GNU_SOURCE
#  endif
#endif


#if defined(WINNT) && (WINNT)
#  include <windows.h>
#  include <process.h>
#  include "getopt.h"
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
#elif defined(DARWIN) && (DARWIN)
#  include <unistd.h>
#  include <getopt.h>
#elif defined(LINUX) && (LINUX)
#  include <unistd.h>
#  include <getopt.h>
#endif


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


#if !defined(NM_HAVE_P_TMPDIR)
#  if defined(WINNT) && (WINNT)
#    define P_tmpdir getenv("TMPDIR")
#  endif
#endif


#if !defined(NM_HAVE_P_TMPDIR)
#  if defined(WINNT)
#    define P_tmpdir getenv("TMPDIR")
#  endif
#endif


#define _unused_(x) ((void)(x))

#define _txt_(x) #x

#define _is_unsigned_type_(t) ((t)~1)


/* #ifdef MSVC */
/* #  include <windows.h> */
/* #  include <tchar.h> */
/* #  define PATH_MAX MAX_PATH */
/* #else */
/* #  ifdef LINUX */
/* #    include <linux/limits.h> */
/* #  else */
/* #    include <limits.h> */
/* #  endif */
/* #  include <libgen.h> */
/* #endif */




#endif /* _NORSTD_H_ */
