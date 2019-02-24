#ifndef _LANG_H_
#define _LANG_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#if MSVC
/* warning C4996: 'strncpy': This function or variable may be
	 unsafe. Consider using strcpy_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS. */
#  pragma warning(disable : 4996)
#elif GCC
#  if NM_HAVE_CC_OPT_IMPLICIT_FALLTHROUGH
#    pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#  endif
#endif

#ifdef NM_HAVE_STDINT_H
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



#endif /* _LANG_H_ */
