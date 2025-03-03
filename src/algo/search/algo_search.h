#ifndef _ALGO_SEARCH_
#define _ALGO_SEARCH_

#include <stddef.h>

void *linear_search (void const *what, void const *base, size_t n, size_t width,
                     int (*cmp) (void const *, void const *));

void *binary_search (void const *key, void const *base, size_t n, size_t width,
                     int (*cmp) (void const *, void const *));


#endif /* _ALGO_SEARCH_ */
