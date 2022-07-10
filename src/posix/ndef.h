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
#  define _unused_(x)  ((void)(x))
#endif  /* _unused_ */


#if !defined(_unused_of_)
#  if defined(CLANG) || defined(GCC)
#    define _unused_of_  __attribute__((unused))
#  else
#    define _unused_of_
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


#define _swp_(a, b, w)                          \
do                                              \
  {                                             \
    size_t __w = (w);                           \
    char *__a = (char *) (a);                   \
    char *__b = (char *) (b);                   \
    do                                          \
      {                                         \
        char __tmp = *__a;                      \
        *__a++ = *__b;                          \
        *__b++ = __tmp;                         \
      } while (--__w > 0);                      \
  } while (0)




#endif /* end of _NDEF_H_ */
