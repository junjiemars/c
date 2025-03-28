#ifndef REAL_H
#define REAL_H

/**
 * Real number
 */
#include <stdbool.h>
#include <stddef.h>

struct Real;

bool from_decimal (bool, unsigned, int, struct Real *);
bool add (struct Real const *, struct Real const *, struct Real *);
bool mul (struct Real const *, struct Real const *, struct Real *);
bool is_normal (struct Real const *);
bool is_sign (struct Real const *);
bool is_nan (struct Real const *);
bool is_inf (struct Real const *);
bool is_zero (struct Real const *);
char *real_str (struct Real *, char *, size_t);
struct Real *new_real (void);
void free_real (struct Real *);

#endif
