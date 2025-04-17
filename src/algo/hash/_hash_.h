#ifndef _HASH__H_
#define _HASH__H_

/*
 * http://www.cs.cornell.edu/courses/cs312/2008sp/lectures/lec21.html
 *
 */

#include <_algo_.h>

extern unsigned long hash (char const *ss);
int insert (const char *ss);
char const *search (char const *ss);
/* void delete (const char *ss); */
/* void print_hash (const char *name, const char *ss, unsigned long hash); */
void test_hash (FILE *in);

#endif /* end of _HASH__H_ */
