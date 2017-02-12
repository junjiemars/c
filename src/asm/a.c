#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _unused_(x) ((void)(x))

int
add1(int n) {
	int v = n+1;
	return v;
}

struct foo {
	int a;
	char b[32];
};

struct foo*
bar(struct foo* s) {
	s->a = add1(s->a);	
	strcpy(s->b, "add1(*foo->a) => %i => %i\n");
	return s;
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
	printf("add1(d) => %i => %i\n", c, d);

	struct foo f = { .a=d, .b="" };	
	struct foo* f1 = bar(&f);
	printf(f1->b, d, f1->a);

}
