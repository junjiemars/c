#ifndef _LNK_H_
#define _LNK_H_

int fn (int);     /* function declaration with external linkage */
extern int state; /* variable declaration with external linkage */

static const int size = 3; /* read-only with internal linkage */
enum
{
  MAX = 10
}; /* constant definition */

#endif /* end of _LNK_H_ */
