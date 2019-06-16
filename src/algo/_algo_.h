#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#define swap(a, b, t)   \
	do {                  \
		t _swap_temp1 = a;	\
		a = b;              \
		b = _swap_temp1;    \
	} while (0)


#endif /* end of _ALGO_H_ */
