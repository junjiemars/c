#ifndef SORT_H
#define SORT_H

void sort(void *base, size_t n, size_t width,
          int (*cmp)(const void *lhs, const void *rhs));


#endif /* end of SORT_H */
