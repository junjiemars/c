#ifndef _NDEF_H_
#define _NDEF_H_


#include <nore.h>
#include <stddef.h>


#if !defined(__has_attribute)
#  if !defined(__attribute__)
#    define __attribute__esc_(...)  __VA_ARGS__
#    define __attribute__(x)  __attribute__esc_  x
#  endif
#endif


#if (MSVC)
#  if !defined(unused) && defined(__attribute__)
#    define unused  __pragma(warning(suppress:4100 4101 4189))
#  endif
#endif


#if !defined(__has_attribute) && defined(__attribute__)
#   if !defined(unused)
#     define unused
#   endif
#endif


#if !defined(__has_attribute) && defined(__attribute__)
#  if !defined(fallthrough)
#    define fallthrough
#  endif
#endif



#if defined(__FUNCTION__)
#  if !(NM_HAVE___FUNC__)
#    undef __FUNCTION__
#  endif
#  define __FUNCTION__
#elif (NM_HAVE___FUNC__)
#  define __FUNCTION__  __func__
#endif  /* __func__ */



#if !(NM_HAVE_RESTRICT)
#  if (NM_HAVE___RESTRICT)
#    if defined(restrict)
#      undef restrict
#    endif
#    define restrict  __restrict
#  else
#    define restrict
#  endif
#endif  /* restrict */


#if !(NM_HAVE_STATIC_ASSERT)
#  if !(NM_HAVE___STATIC_ASSERT)
#    define static_assert(e, m)  enum {static_assert = 1/!!((e) && (m))}
#  else
#    if defined(static_accsert)
#      undef static_assert
#    endif
#    define static_assert  _Static_assert
#  endif
#endif  /* static_assert */


#if !(NM_HAVE_ALIGNOF)
#  if !(NM_HAVE__ALIGNOF)
#    if defined(alignof)
#      undef alignof
#    endif
#    define alignof __alignof__
#  else
#    include <stdalign.h>
#  endif
#else
#  include <stdalign.h>
#endif  /* alignof */


#if !(NM_HAVE_ALIGNAS)
#  if !(NM_HAVE__ALIGNAS)
#    if defined(alignas)
#      undef alignas
#    endif
#    define alignas(x) __attribute__((aligned(x)))
#  else
#    include <stdalign.h>
#  endif
#else
#  include <stdalign.h>
#endif  /* alignas */


#if (NM_HAVE_GENERIC)
#  define generic _Generic
#else
#  define generic
#endif  /* generic */




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


#if !defined(_cat_)
#  define _cat_(a, b)  a##b
#endif  /* _cat_ */


#define _swp_(a, b, w)                            \
do                                                \
  {                                               \
    int    w1_ =  (int) (w);                      \
    int    n1_ =  (w1_ + 7) / 8;                  \
    char  *a1_ =  (char *) (a);                   \
    char  *b1_ =  (char *) (b);                   \
    char   t1_ =  0;                              \
    switch (w1_ % 8) {                            \
    case 0: do { t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 7:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 6:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 5:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 4:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 3:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 2:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
        __attribute__((fallthrough));             \
    case 1:      t1_=*a1_;*a1_++=*b1_;*b1_++=t1_; \
               } while (--n1_ > 0);               \
    }                                             \
  } while (0)




#endif /* end of _NDEF_H_ */
