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


#define _hton16_(x) ((((uint16_t)(x) & 0xff) << 8) | (uint16_t)(x) >> 8)

#define _hton32_(x)                             \
  (((uint32_t)_hton16_(x) << 16)                \
   | ((uint32_t)_hton16_((uint32_t)(x) >> 16)))

#define _hton64_(x)                             \
  (((uint64_t)_hton32_(x) << 32)                \
   | ((uint64_t)_hton32_((uint64_t)(x) >> 32)))


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
