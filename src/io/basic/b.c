#include "_io_.h"

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	int ch;
	while (EOF != (ch = fgetc(stdin))) {
		fputc(ch, stdout);
	}
	if (ferror(stdin)) {
		perror("read failed from stdin");
		return 1;
	}

	return 0;
}
