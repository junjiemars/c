#include <nm_auto_config.h>
#include <nm_auto_headers.h>
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
}

