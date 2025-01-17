#ifndef REAL_H
#define REAL_H

/**
 * Real number
 */
#include <stddef.h>

struct Real;

int real_from_decimal (int, unsigned int, struct Real *);
int real_add (struct Real *, struct Real *, struct Real *);
char *real_str (struct Real *, char *, size_t);
struct Real *new_real (void);
void free_real (struct Real *);

#endif
