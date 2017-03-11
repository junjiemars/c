#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <stdlib.h>

/*
#ifdef CC_GCC
#define __cdecl __attribute__((cdecl))
#define __stdcall __attribute__((stdcall))
#endif
*/

long
factorial(long n, long acc) {
	if (n < 1) {
		return acc;
	} else {
		return factorial(n-1, n*acc);
	}
}

long
add(long a, long b, long *c) {
	long v = a + b + *c;
	v = factorial(v, 1);
	*c += 1;
	return v;
}

int
main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("input 2 integer oprands\n");
		return -1;
	}

	long a, b, c, v;

	a = atol(argv[1]);
	b = atol(argv[2]);
	c = atol(argv[3]);

	v = add(a, b, &c);
	
	printf("cdecl=> add(%li,%li,%li)=%li\nc=%li\n", a, b, c, v, c);		
	
}
