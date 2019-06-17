#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#define swap(a, b, width) 				  \
	do {                              \
	  unsigned char _swap1[width];		\
		memcpy(_swap1, (a), (width));	  \
		memmove((a), (b), (width));		  \
		memcpy((b), _swap1, (width));	  \
	} while (0)

#endif /* end of _ALGO_H_ */
