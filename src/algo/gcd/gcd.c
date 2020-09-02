#include <_algo_.h>
#include <stdio.h>
#include <stdlib.h>


/* iterative */
int gcd_iter(int a, int b);
/* tail recursive */
int gcd_tr(int a, int b);

int
gcd_iter(int a, int b) {
	while (b) {
		int m = a % b;
		a = b;
		b = m;
	}
	return a;
}

int
gcd_tr(int a, int b) {
	if (0 == b) {
		return a;
	} 
	return gcd_tr(b, a % b);
}

int
main(int argc, char **argv) {
	if (argc < 3) {
		printf("gcd_iter(a, b)\n");
		return 1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("iterative: gcd(%i, %i) = %i\n", a, b, gcd_iter(a, b));
	printf("recursive: gcd(%i, %i) = %i\n", a, b, gcd_tr(a, b));
	
	return 0;
}
