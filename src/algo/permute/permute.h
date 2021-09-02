#ifndef PERMUTE_H_
#define PERMUTE_H_

/* 
 * Permutation:
 *
 *   0 1 0       x1     x2
 *   0 0 1   *   x2  =  x3
 *   1 0 0       x3     x1
 *
 */
void permute(void *base, size_t n, size_t width,
             const size_t *permutation, size_t size,
             int (*cmp)(const void *, const void *));


#endif /* end of PERMUTE_H_ */
