#include <stdio.h>
#include <stdlib.h>

int 
factorial(int n, int acc) {
	if (n < 0) return 0;
	if (0 == n) return 1;
	
	if (1 == n) {
		return acc;
	} else {
		return factorial(n-1, n*acc);
	}
}

int 
main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("pls, input N to calculate factorial(N)");
		return 1;
	}

	int n = atoi(argv[1]);
	int acc = 1;
	int f = factorial(n, acc);

	printf("factorial(%i)=%i\n", n, f);
	

}
