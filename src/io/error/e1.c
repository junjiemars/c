#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	char *path = "e1.c";
	FILE *file = fopen(path, "r");
	if (0 == file) {
		int errnum = errno;
		printf("!panic: %s\n", strerror(errnum));
		perror("!panic");
		perror(0);
	} else {
		fclose(file);
	}
	
	return 0;
}
