#ifndef _NDEF_H_
#define _NDEF_H_


#include <nore.h>


#if !(NM_HAVE_RESTRICT)
#  if (NM_HAVE___RESTRICT)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif  /* NM_HAVE_RESTRICT */


#if defined(NDEBUG) && (NDEBUG)
#  if defined(assert)
#    undef assert
#  endif
#  define assert(x) ((void)(x))
#endif  /* assert */


#if !defined(_unused_)
#  define _unused_(x) ((void)(x))
#endif  /* _unused_ */


#if !defined(_isut_)
#  define _isut_(t) (((t)~1) > 0)
#endif  /* _isut_ */


#if !defined(_nof_)
#  define _nof_(a) (sizeof(a)/sizeof(*(a)))
#endif  /* _nof_ */



#endif /* end of _NDEF_H_ */
