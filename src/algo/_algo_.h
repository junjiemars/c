#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#define _unused_(x) ((void)(x))

#define swap(a, b, w) do {                      \
		unsigned char _swap_1_[w];                  \
		memcpy(_swap_1_, (a), (w));                 \
		memmove((a), (b), (w));                     \
		memcpy((b), _swap_1_, (w));                 \
	} while (0)


void list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el));

void print_int(const void *el);
void print_str(const void *el);

int comp_int(const void *lhs, const void *rhs);
int comp_str(const void *lhs, const void *rhs);

#endif /* end of _ALGO_H_ */
