#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>
#include <ndef.h>
#include <nint.h>
#include <nstr.h>
#include <nasrt.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


#if (MSVC)
#pragma warning(disable:4996)
#endif

/* #define _unused_(x) ((void)(x)) */

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


#ifndef max
#  define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#  define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifdef count
#  undef count
#endif
#define count(a) sizeof(a)/sizeof(*a)

#ifdef offset
#  undef offset
#endif
#define offset(l, r, w) (((char*) (r) - (char*) (l)) / (w))

struct score_s
{
  char  name[32];
  int   score;
};


void list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el));

void print_int(const void *e);
void print_str(const void *e);
void print_size_t(const void *e);
void print_score_s(const void *e);

int cmp_int(const void *lhs, const void *rhs);
int cmp_str(const void *lhs, const void *rhs);
int cmp_score_s(const void *lhs, const void *rhs);

int verify(const void *lhs, const void *rhs, size_t size);

#endif /* end of _ALGO_H_ */
