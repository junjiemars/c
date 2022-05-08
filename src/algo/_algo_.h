#ifndef _ALGO_H_
#define _ALGO_H_

#include <nore.h>
#include <ncstd.h>
#include <stdlib.h>


#if (MSVC)
#pragma warning(disable:4996)
#endif


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
