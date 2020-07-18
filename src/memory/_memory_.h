#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "nore.h"
#include "ints.h"
#include <assert.h>

#ifdef _unused_
#  undef _unused_
#endif
#define _unused_(x) ((void)(x))

#ifdef _sizeof_array_
#  undef _sizeof_array_
#endif
#define _sizeof_array_(a) sizeof((a))/sizeof((a)[0])

#ifdef _bool_
#  undef _bool_
#endif
#define _bool_(p) ((p) ? "true" : "false")




#ifdef NM_HAVE_STDBOOL_H
#  include <stdbool.h>
#endif /* end of NM_HAVE_STDBOOL_H */


#ifdef MSVC
#  pragma warning(disable : 4996) /* _CRT_SECURE_NO_WARNINGS */
#  pragma warning(disable : 4214) /* bit field types other than int */
#endif

#ifdef RISKY
#  ifdef MSVC
#    pragma warning(disable : 4090) /* different const qualifiers */
#    pragma warning(disable : 4244)
#    pragma warning(disable : 4204) /* or Compiler Option: -Ze */
#    pragma warning(disable : 4789) /* will be overrun */
#  endif /* end of MSVC */
#endif /* end of RISKY */


#endif /* end of _MEMORY_H_ */
