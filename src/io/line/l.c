#include <_io_.h>
#include <stdio.h>

void
read_lines(const char *filename, const int max_line_size) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}
	int c;
	char line[max_line_size];
	char *p = line;
	while (EOF != (c = fgetc(file))) {
		if ('\r' == c || '\n' == c) {
			*p = 0;
			printf("%s\n", line);
			p = line;
		} else {
			*p++ = c;
		}
	}
	if (ferror(file)) {
		perror(filename);
		goto close_exit;
	}
 close_exit:
	fclose(file);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		read_lines(argv[1], 16);
	}
	return 0;
}
