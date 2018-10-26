
#ifndef _LANG_H_
#define _LANG_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#if MSVC
/* C4477: 'printf' : format string '%llu' requires 
   an argument of type 'unsigned __int64', but variadic 
   argument 2 has type 'unsigned long' */
#  pragma warning(disable : 4477)
#  pragma warning(disable : 4702)
#  pragma warning(disable : 4996)
#endif


#endif /* _LANG_H_ */
