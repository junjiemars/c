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


/* #ifdef static_assert */
/* #  undef static_assert */
/* #endif */

/* #if !(NM_HAVE_STATIC_ASSERT) */
/* #  define static_assert(e, m) enum {static_assert = 1/!!((e) && (m))} */
/* #else */
/* #  define static_assert _Static_assert */
/* #endif  /\* NM_HAVE_STATIC_ASSERT *\/ */


#if !defined(_unused_)
#  define _unused_(x)  ((void)(x))
#endif  /* _unused_ */


#if !defined(_isut_)
#  define _isut_(t)  (((t)~1) > 0)
#endif  /* _isut_ */


#if !defined(_nof_)
#  define _nof_(a)  (sizeof(a)/sizeof(*(a)))
#endif  /* _nof_ */


#if !defined(_diff_)
#  define _diff_(l, r, w)  (((char*)(r)-(char*)(l))/(w))
#endif  /* _diff_ */


#if !defined(_max_)
#  define _max_(a, b)  (((a) > (b)) ? (a) : (b))
#endif  /* _max_ */


#if !defined(_min_)
#  define _min_(a, b)  (((a) < (b)) ? (a) : (b))
#endif  /* _min_ */


#if !defined(_str_)
#  define _str_(s)  #s
#endif  /* _str_ */



#endif /* end of _NDEF_H_ */
