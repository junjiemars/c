#ifndef _X86_H_
#define _X86_H_

#include <nore.h>

#define _unused_(x)  ((void) (x))


#ifdef MSVC
#pragma warning(disable : 4996) /*_CRT_SECURE_NO_WARNINGS*/
#pragma warning(disable : 4244) /* possiable loss of data */
#pragma warning(disable : 4305) /* truncation from 'double' to 'float' */
#pragma warning(disable : 4700) /* uninitialize local variable */
#endif

#ifdef GCC
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#endif


struct binky
{
  int    a;
  char   b, c, d, e;
  short  f;
};

struct fraction
{
	int  numerator;
	int  denominator;
};

struct fraction2
{
  long long  numerator;
  long long  denominator;
};



#endif /* _X86_H_ */
