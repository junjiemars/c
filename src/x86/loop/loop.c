#include <_x86_.h>
#include <stdio.h>
#include <stdlib.h>

void 
swap_int(int *a, int *b) {
	int a_, b_;

	a_ = *a;
	b_ = *b;
	
	*a = b_;	
	*b = a_;
}

void
swap_long(long *a, long *b) {
	long a_, b_;
	
	a_ = *a;
	b_ = *b;

	*a = b_;
	*b = a_;
}

int
factorial_while(int n) {
	int f = 1;
	while (n > 0) {
		f *= n--;
	}
	return f;
}

int 
factorial_do(int n) {
	int f = 1;
	do {
		f *= n--;	
	} while (n > 0);
	return f;
}

int
factorial_goto(int n) {
	int f = 1;
loop:
	f *= n--;
	if (n > 0) goto loop;
	return f;
}

int 
factorial_while_goto(int n) {
	int f = 1;
	goto middle;
loop:
	f *= n--;
middle:
	if (n > 1) goto loop;
	return f;
}

int
main(int argc, char* argv[]) {
	int n = 9;
	
	if (argc > 1) n = atoi(argv[1]);

	int x, y, z;

	while (1) {
		x = 0;
		y = 1;
		int c = 2;
		
		do {
			printf("%i ", x);

			z = x + y;
			x = y;
			y = z;	
			
		} while (c++ <= n);

		putchar('\n');
		break;
	}

	printf("before swap_int: x=%i,y=%i\n", x, y);
	swap_int(&x, &y);
	printf("after swap_int:  x=%i,y=%i\n", x, y);
	
	long x1 = (long)y;
	long y1 = (long)x;

	printf("before swap_long: x=%li,y=%li\n", x1, y1);
	swap_long(&x1, &y1);
	printf("after swap_long:  x=%li,y=%li\n", x1, y1);

	printf("factorial_while(%i)=%i\n", n, factorial_while(n));
	printf("factorial_do(%i)=%i\n", n, factorial_do(n));
	printf("factorial_goto(%i)=%i\n", n, factorial_goto(n));
	printf("factorial_while_goto(%i)=%i\n", n, factorial_while_goto(n));
}

