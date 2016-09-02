#include <stdio.h>


int main(int argc, const char *argv[]) {

	if (argc > 1) {
		printf("Hi, %s\n", argv[1]);
	} else {
		printf("Hello, world!\n");
	}

	return 0;
}
