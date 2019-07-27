#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#define _unused_(x) ((void)(x))

#define swap(a, b) 				               \
	do {                                   \
		unsigned char _swap_t1[sizeof(a)];	 \
		size_t _swap_w1 = sizeof(a);         \
		memcpy(_swap_t1, (a), _swap_w1);	   \
		memmove((a), (b), _swap_w1);		     \
		memcpy((b), _swap_t1, _swap_w1);	   \
	} while (0)


void list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el));

void print_int(const void *el);
void print_str(const void *el);

int comp_int(const void *lhs, const void *rhs);
int comp_str(const void *lhs, const void *rhs);

#endif /* end of _ALGO_H_ */
