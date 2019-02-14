#include <_io_.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("stdin=%d, stdout=%d, stderr=%d\n",
				 fileno(stdin),
				 fileno(stdout),
				 fileno(stderr));
	
	return 0;
}
