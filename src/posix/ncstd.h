/**
 * Nore C standard
 */
#ifndef _NCSTD_H_
#define _NCSTD_H_

#include <nore.h>

#include <ndef.h>
#include <nint.h>
#include <nstr.h>


#if !defined(_fpos_)
#  if (LINUX)
#    define _fpos_(x)  x.__pos
#  else
#    define _fpos_(x)  x
#  endif
#endif


#define _flip16_(x)                               \
  ((uint16_t)((((uint16_t)(x) & 0x00ff) << 8)     \
              | (((uint16_t)(x) & 0xff00) >> 8)))

#define _flip32_(x)                                         \
  ((uint32_t)(((uint32_t)_flip16_(x) << 16)                 \
              | ((uint32_t)_flip16_((uint32_t)(x) >> 16))))

#define _flip64_(x)                                         \
  ((uint64_t)(((uint64_t)_flip32_(x) << 32)                 \
              | ((uint64_t)_flip32_((uint64_t)(x) >> 32))))


#define _hi8_(x) (((uint8_t)(x) >> 4) & (uint8_t)0x0f)
#define _lo8_(x) ((uint8_t)(x) & (uint8_t)0x0f)


#include <time.h>
#define _time_(E, R)                            \
do                                              \
{                                               \
  clock_t s, e;                                 \
  s = clock();                                  \
  (E);                                          \
  e = clock();                                  \
  R = (e-s)/(double)CLOCKS_PER_SEC;             \
} while (0)


#if (WINNT)
#  if defined(setenv)
#    undef  setenv
#  endif
#  define setenv(n, v, _)  _putenv_s((n), (v))
#  if defined(unsetenv)
#    undef  unsetenv
#  endif
#  define unsetenv(n)   _putenv_s((n), "")

#endif  /* setenv, unsetenv */


#if (MSVC)
#  if defined(environ)
#    undef environ
#  endif
#  define environ  _environ
#endif  /* environ */

#if (WINNT) && (GCC)
#  if defined(NM_NEED_ENVIRON)
#    undef NM_NEED_ENVIRON
#  endif
#else
#  define NM_NEED_ENVIRON 1
#endif

#endif /* _NCSTD_H_ */
