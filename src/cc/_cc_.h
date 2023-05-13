#ifndef _CC_H_
#define _CC_H_

#include <nore.h>
#include <ncstd.h>
#include <nasrt.h>
#include <nio.h>

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>


#if MSVC
#  pragma warning(disable:4996)
#endif

#if GCC
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

#if CLANG
#  pragma clang diagnostic ignored "-Wunused-function"
#  pragma clang diagnostic ignored "-Wsign-compare"
#endif

#endif /* end of _CC_H_ */
