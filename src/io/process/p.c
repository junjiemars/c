#include <_io_.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);
	
	FILE* out = popen("ls", "r");
	if (!out) {
		return ferror(out);
	}

	char s[512];
	while (0 != fgets(s, sizeof(s), out)) {
		printf("%s", s);
	}
	if (feof(out)) {
		putc('\n', stdout);
	} else {
		fprintf(stderr, "!panic: ferror(out) = %d\n", ferror(out));
	}
	pclose(out);
	
	return 0;
}
