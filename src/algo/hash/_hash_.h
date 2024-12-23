#ifndef _HASH__H_
#define _HASH__H_

/*
 * http://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html
 *
 */

#include "../_algo_.h"

unsigned long hash (const char *ss);

void print_hash (const char *name, const char *ss, unsigned long hash);

#endif /* end of _HASH__H_ */
