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



#if !defined(_unused_)
#  if (CLANG) || (GCC)
#    define _unused_(x)  __attribute__((unused)) x
#  elif (MSVC)
#    define _unused_(x)  __pragma(warning(suppress:4100 4101 4189)) x
#  else
#    define _unused_(x)  x
#  endif
#endif


#if !defined(_isut_)
#  define _isut_(t)  (((t)~1) > 0)
#endif  /* _isut_ */


#if !defined(_nof_)
#  define _nof_(a)  (sizeof(a)/sizeof(*(a)))
#endif  /* _nof_ */


#if !defined(_diff_)
#  define _diff_(l, r, w)  (((char*)(r) - (char*)(l)) / (w))
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


#if !defined(_fallthrough_)
#   if (GCC)
#     define _fallthrough_  __attribute__((fallthrough))
#   else
#     define _fallthrough_
#   endif
#endif

#define _swp_(a, b, w)                                          \
do                                                              \
  {                                                             \
    int    w1_ =  (int) (w);                                    \
    int    n1_ =  (w1_ + 7) / 8;                                \
    char  *a1_ =  (char *) (a);                                 \
    char  *b1_ =  (char *) (b);                                 \
    char   t1_ =  0;                                            \
    switch (w1_ % 8) {                                          \
    case 0: do { t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 7:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 6:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 5:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 4:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 3:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 2:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;_fallthrough_; \
    case 1:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_;               \
               } while (--n1_ > 0);                             \
    }                                                           \
  } while (0)




#endif /* end of _NDEF_H_ */
