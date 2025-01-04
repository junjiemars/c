#ifndef _GEO_H_
#define _GEO_H_

#include <nore.h>


#if (WINNT)
#  if (0 == SHARED)
#    define GEO_API __declspec(dllexport) __stdcall
#  elif (1 == SHARED)
#    define GEO_API __declspec(dllimport) __stdcall
#  endif /* SHARED */
#else
#  define GEO_API
#endif /* WINNT */


#ifdef __cplusplus
extern "C" {
#endif

double GEO_API area_of_rect(double, double);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif /* _GEO_H_ */
