#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <stdio.h>

#define _unused_(x) ((void)(x))

int
add1(int n) {
	return (n+1);
}

int
sub1(int n) {
	return (n-1);
}

typedef int (*op)(int n);

int
fn1(int n, op fn) {
	return fn(n);
}  

enum { ADD1, SUB1 };

op
fn2(int op) {
	if (ADD1 == op) return &add1;
	if (SUB1 == op) return &sub1;
	return 0;
}

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	int i1 = 0x11223344;
	printf("fn1(add1:%d)=%d\n", i1, fn1(i1, &add1));
	printf("fn1(sub1:%d)=%d\n", i1, fn1(i1, &sub1));

	printf("fn2(ADD1:%d)=%d\n", i1, fn2(ADD1)(i1));
	printf("fn2(SUB1:%d)=%d\n", i1, fn2(SUB1)(i1));

}
