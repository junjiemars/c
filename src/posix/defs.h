#ifndef _DEFS_H_
#define _DEFS_H_


#include <nore.h>


#if !(NM_HAVE_RESTRICT)
#  if (NM_HAVE___RESTRICT)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif  /* NM_HAVE_RESTRICT */


#include <assert.h>
#if !(NM_HAVE_STATIC_ASSERT)
#  ifdef static_assert
#    undef static_assert
#  endif
#  define static_assert(e, m) enum {static_assert = 1/!!((e) && (m))}
#endif  /* NM_HAVE_STATIC_ASSERT */


#if (NDEBUG)
#  if defined(assert)
#    undef assert
#  endif
#  define assert(x) ((void)(x))
#endif  /* assert */


#if !defined(_unused_)
#  define _unused_(x) ((void)(x))
#endif  /* _unused_ */


#endif /* end of _DEFS_H_ */
