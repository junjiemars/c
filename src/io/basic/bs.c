#include "_io_.h"
#include <stdio.h>

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	int ch;
	while (EOF != (ch = getc(stdin))) {
		putc(ch, stdout);
	}
}
