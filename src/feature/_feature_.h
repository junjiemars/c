#ifndef _FEATURE_H_
#define _FEATURE_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#if defined(CLANG)
#  if __has_attribute(noinline)
#    define __noinline__ __attribute__((noinline))
#  else
#    define __noinline__
#  endif
#
#  if __has_attribute(foreinline)
#    define __always_inline__ __attribute__((always_inline))
#  else
#    define __always_inline__
#  endif
#endif

#endif /* _FEATURE_H_ */
