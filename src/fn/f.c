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
recursive_factorial(int n) {
	if (n < 0) return 0;
	if (n < 2) {
		return 1;
	} else {
		return n*recursive_factorial(n-1);
	}
}

static inline int 
_iter_fact(int n, int acc) {
	if (n == 1) {
		return acc;
	} else {
		return _iter_fact(n-1, n*acc);
	}
}

int
iterative_factorial(int n) {
	if (n < 0) return 0;
	return _iter_fact(n, 1);
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

	int f1 = 10;
	printf("recursive_factorial(%i)=%i\n", f1, recursive_factorial(f1));
	printf("iterative_factorial(%i)=%i\n", f1, iterative_factorial(f1));

}
