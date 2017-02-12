#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))

int
add1(int n) {
	int v = n+1;
	return v;
}

int
main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("input 2 args: a, b\n");
		printf("----------\n");
		return -1;
	}

	int a, b, c, d;
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	c = a+b;
	printf("c=a+b => %i+%i=%i\n", a, b, c);

	d = add1(c);
	printf("add1(d) => %i=%i\n", c, d);

}
