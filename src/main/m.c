#include <stdio.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))

void
on_exit(void) {
	printf("----------\n");
	printf("exiting...\n");
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	atexit(&on_exit);

	for (int i=0; i<argc; i++) {
		printf("%s\n", argv[i]);
	}

	for (char** p=argv; *p!=0; p++) {
		printf("%s\n", *p);
	}

	/* return 0; */
}
