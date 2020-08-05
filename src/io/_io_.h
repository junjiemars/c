#ifndef _IO_H_
#define _IO_H_

#include <nore.h>
#include "restrict.h"

#if (MSVC)
#  pragma warning(disable : 4996)
#  pragma warning(disable: 4244)
#endif

#define _unused_(x) ((void)(x))

void hex_out(const char *ss);

#endif /* end of _IO_H_ */
