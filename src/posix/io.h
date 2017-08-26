#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef MSVC

	#define io_fopen(e, f, n, m) { e = fopen_s(&f, n, m); }
	#define io_fprintf(e, f, ...) { e = fprintf_s(f, __VA_ARGS__); }

#else

	#define io_fopen(e, f, n, m) { f = fopen(n, m); e = errno; }
	#define io_fprintf(e, f, ...) { fprintf(f, __VA_ARGS__); e = errno; }

#endif

#endif
