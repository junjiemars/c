#include <_algo_.h>
#include <stdio.h>
#include <stdlib.h>


/* raw while loop */
int
gcd(int a, int b) {
	while (b) {
		int m = a % b;
		a = b;
		b = m;
	}
	return a;
}

/* tail recursion */
int
gcd1(int a, int b) {
	if (0 == b) {
		return a;
	} 
	return gcd1(b, a % b);
}

int
main(int argc, char **argv) {
	if (argc < 3) {
		printf("gcd(a, b)\n");
		return 1;
	}
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("gcd(%i, %i) = %i\n", a, b, gcd(a, b));
	printf("gcd1(%i, %i) = %i\n", a, b, gcd1(a, b));
	
	return 0;
}
