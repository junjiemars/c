#ifndef _PRIME_H_
#define _PRIME_H_

#include <stdbool.h>

int *new_prime (int l, int r);
void prime_sieve (int l, int r, int *);
void prime_print (int l, int r, int *);
bool prime_check (int);

#endif /* _PRIME_H_ */
