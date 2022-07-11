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


#define _swp_(a, b, w)                                            \
do                                                                \
  {                                                               \
    int    __w1  =  (int) (w);                                    \
    int    __n1  =  (__w1 + 7) / 8;                               \
    char  *__a1  =  (char *) (a);                                 \
    char  *__b1  =  (char *) (b);                                 \
    char   __t1  =  0;                                            \
    switch (__w1 % 8) {                                           \
      case 0: do { __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 7:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 6:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 5:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 4:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 3:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 2:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
      case 1:      __t1 = *__a1; *__a1++ = *__b1; *__b1++ = __t1; \
                 } while (--__n1 > 0);                            \
    }                                                             \
  } while (0)




#endif /* end of _NDEF_H_ */
