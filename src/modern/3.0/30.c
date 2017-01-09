#include <stdio.h>
#include <stdlib.h>
/* #include <stdbool.h> bool: true/false */

#define _unused_(x) (void)(x)

int main(int argc, char* argv[argc+1]) {
	_unused_(argv);

	puts("Hello world!");
	if (argc > 1) {
		int i = 0;
		while (i++ < argc-1) {
			puts("loop step ...");
		}
	} else {
		do {
			puts("but this one does");
		} while (0);
	}

	return EXIT_SUCCESS;
}
