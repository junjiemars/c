#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <ndef.h>
#include <assert.h>


#ifdef _bool_
#  undef _bool_
#endif
#define _bool_(p) ((p) ? "true" : "false")

#ifdef MSVC
#  pragma warning(disable : 4996) /* _CRT_SECURE_NO_WARNINGS */
#  pragma warning(disable : 4214) /* bit field types other than int */
#endif

#ifdef _RISKY_
#  ifdef MSVC
#    pragma warning(disable : 4090) /* different const qualifiers */
#    pragma warning(disable : 4244)
#    pragma warning(disable : 4204) /* or Compiler Option: -Ze */
#    pragma warning(disable : 4789) /* will be overrun */
#  endif /* end of MSVC */
#endif /* end of _RISKY_ */


#endif /* end of _MEMORY_H_ */
