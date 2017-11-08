#ifndef _X86_H_
#define _X86_H_

#include <nore.h>

#define _unused_(x) (void)(x)


#ifdef MSVC
#pragma warning(disable : 4996) /*_CRT_SECURE_NO_WARNINGS*/
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#endif

#ifdef GCC
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif


#endif
