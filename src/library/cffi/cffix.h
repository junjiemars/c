#ifndef _CFFIX_H_
#define _CFFIX_H_

#include "nore.h"
#include <stddef.h>


#if (MSVC)
#  if (1 == SHARED)
#    define CFFIX_API __declspec(dllexport) __stdcall
#  elif (0 == SHARED)
#    define CFFIX_API __declspec(dllimport) __stdcall
#  endif /* SHARED */
#else
#  define CFFIX_API
#endif /* MSVC */


#ifdef __cplusplus
extern "C" {
#endif

  int CFFIX_API inc(int);
  size_t CFFIX_API str_len(const char *ss);

#ifdef __cplusplus
}
#endif  /* __cplusplus */


#endif /* _CFFIX_H_ */
