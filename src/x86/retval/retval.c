#include "_x86_.h"
#include <stdlib.h>

static int   foo(void);
static int  *bar(void);


int
main(void)
{
	int   a;
  int  *b;

  a = foo();
  b = bar();
  free(b);
}

int
foo(void)
{
	int  a;
	int  b;

	b = 1;
	a = b + 2;
	return a;
}

int *
bar(void)
{
  int  *a;

  a = malloc(sizeof(int) * 4);
  return a;
}
