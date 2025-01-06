/**
 * Nore C standard
 */
#ifndef _NCSTD_H_
#define _NCSTD_H_

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
#  if (MSVC)
#    if defined(environ)
#      undef environ
#    endif
#    define environ  _environ
#  endif
#endif  /* setenv, unsetenv */


#endif /* _NCSTD_H_ */
