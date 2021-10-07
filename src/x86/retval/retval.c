#include "_x86_.h"
#include <stdlib.h>

int
foo()
{
	int a;
	int b;
	b = 1;
	a = b + 2;	
	return a;
}

int *
bar()
{
  int *a;
  a = malloc(sizeof(int) * 4);
  return a;
}

int 
main()
{
	int a;
  int *b;
  a = foo();
  b = bar();
}
