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

int
add(int a, int b, int *c) {
	int v = a + b + *c;
	*c += 1;
	return v;
}

int
main(int argc, char* argv[]) {
	if (argc < 4) {
		printf("input 2 integer oprands\n");
		return -1;
	}

	int a, b, c, v;

	a = atoi(argv[1]);
	b = atoi(argv[2]);
	c = atoi(argv[3]);

	v = add(a, b, &c);
	
	printf("cdecl=> add(%i,%i,%i)=%i\nc=%i\n", a, b, c, v, c);		
	
}
