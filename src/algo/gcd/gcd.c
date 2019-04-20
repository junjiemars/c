#include <_algo_.h>
#include <stdio.h>
#include <stdlib.h>


int
gcd(int a, int b) {
	if (0 == b) {
		return a;
	} 
	return gcd(b, a % b);
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
	
	return 0;
}
