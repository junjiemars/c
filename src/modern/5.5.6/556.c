#include <modern.h>
#include <stdint.h>
/* #include <limits.h> */
#include <stdio.h>

/* 
	signed limits:
 	#define INT(N)_MIN (-INT(N)_MAX-1), or from -2^(N) to 2^(N-1)-1
*/

int main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("INT16_MIN+INT16_MAX=%d\n", INT16_MIN+INT16_MAX);
	printf("two's complement if 3==(-1&3)=%d\n", -1&3);

	return 0;
}
