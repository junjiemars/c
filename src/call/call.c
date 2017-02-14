#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef CC_GCC
#define __cdecl __attribute__((cdecl))
#define __stdcall __attribute__((stdcall))
#endif

int __cdecl 
add(int a, int b) {
	int v = a+b;
	return v;
}

int __stdcall
sub(int a, int b) {
	int v = a-b;
	return v;
}

int
main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("input 2 integer oprands\n");
		return -1;
	}

	int a, b, v1, v2;

	a = atoi(argv[1]);
	b = atoi(argv[2]);

	v1 = add(a, b);
	v2 = sub(v1, b);
	
	printf("cdecl=> add(%i,%i)=%i\n", a, b, v1);		
	printf("stdcall=> sub(%i,%i)=%i\n", v1, b, v2);		
	
}
