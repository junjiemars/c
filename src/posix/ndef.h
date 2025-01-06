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
#    define unused  __pragma(warning(suppress: 4100 4101 4189))
#  endif
#endif


#if !defined(__has_attribute) && defined(__attribute__)
#   if !defined(unused)
#     define unused
#   endif
#endif

#if (MSVC)
#  if !defined(fallthrough) && defined(__attribute__)
#    define fallthrough  __pragma(warning(suppress: 26819))
#  endif
#endif

#if !defined(__has_attribute) && defined(__attribute__)
#  if !defined(fallthrough)
#    define fallthrough
#  endif
#endif



#if !defined(restrict)
#  if defined(NM_HAVE_RESTRICT) && (NM_HAVE_RESTRICT)
#    define restrict  __restrict
#  else
#    define restrict
#  endif
#endif  /* restrict */



#if !defined(static_assert)
#  if defined(NM_HAVE_STATIC_ASSERT) && (NM_HAVE_STATIC_ASSERT)
#    define static_assert  _Static_assert
#  else
#    define static_assert(e, m)  enum {static_assert = 1/!!((e) && (m))}
#  endif
#endif  /* static_assert */



#if !defined(alignas)
#  if defined(NM_HAVE_ALIGNAS) && (NM_HAVE_ALIGNAS)
#    define alignas  _Alignas
#  elif defined(MSVC) && (MSVC)
#    define alignas(x)  __declspec(align(x))
#  else
#    define alignas(x)  __attribute__((aligned(x)))
#  endif
#endif  /* alignas */


#if !defined(alignof)
#  if defined(NM_HAVE_ALIGNOF) && (NM_HAVE_ALIGNOF)
#    define alignof  _Alignof
#  elif defined(MSVC) && (MSVC)
#    define alignof  __alignof
#  else
#    define alignof  __alignof__
#  endif
#endif  /* alignof */


#if !defined(complex)
#  if defined(NM_HAVE_COMPLEX) && (NM_HAVE_COMPLEX)
#    define complex  _Complex
#  endif
#endif  /* complex */


#if !defined(generic)
#  if defined(NM_HAVE_GENERIC) && (NM_HAVE_GENERIC)
#    define generic  _Generic
#  endif
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
