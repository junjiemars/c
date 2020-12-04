#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <assert.h>

#define _unused_(x) ((void)(x))

#if (MSVC)
/* msvc does not support variable length array, C2057 */
#define swap(a, b, w) do {                      \
    unsigned char *_swap_1_ = malloc(w);        \
		memcpy(_swap_1_, (a), (w));                 \
		memmove((a), (b), (w));                     \
		memcpy((b), _swap_1_, (w));                 \
    free(_swap_1_);                             \
	} while (0)
#else
#define swap(a, b, w) do {                      \
		unsigned char _swap_1_[w];                  \
		memcpy(_swap_1_, (a), (w));                 \
		memmove((a), (b), (w));                     \
		memcpy((b), _swap_1_, (w));                 \
	} while (0)
#endif

#ifndef MAX
#  define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#  define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

void list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el));

void print_int(const void *el);
void print_str(const void *el);

int cmp_int(const void *lhs, const void *rhs);
int cmp_str(const void *lhs, const void *rhs);

int verify(const void *lhs, const void *rhs, size_t size);

#endif /* end of _ALGO_H_ */
