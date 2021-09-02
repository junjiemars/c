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

#define swap(a, b, w)                           \
do                                              \
  {                                             \
    size_t __w = (w);                           \
    char *__a = (char *) (a);                   \
    char *__b = (char *) (b);                   \
    do                                          \
      {                                         \
        char __tmp = *__a;                      \
        *__a++ = *__b;                          \
        *__b++ = __tmp;                         \
      } while (--__w > 0);                      \
  } while (0)


#ifndef MAX
#  define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#  define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifdef count
#  undef count
#endif
#define count(a) sizeof(a)/sizeof(*a)

#ifdef offset
#  undef offset
#endif
#define offset(l, r, w) (((char*) (r) - (char*) (l)) / (w))

void list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el));

void print_int(const void *el);
void print_str(const void *el);
void print_size_t(const void *el);

int cmp_int(const void *lhs, const void *rhs);
int cmp_str(const void *lhs, const void *rhs);

int verify(const void *lhs, const void *rhs, size_t size);

#endif /* end of _ALGO_H_ */
