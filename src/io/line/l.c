#include <_io_.h>
#include <stdio.h>
#include <stdlib.h>

#if MSVC
#  pragma warning(disable: 4244)
#endif

void
read_lines(const char *filename,
					 size_t linecap,
					 int delimiter,
					 void (*process_line)(const char *line, ssize_t linelen)) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}
	int c;
	char *line = malloc(linecap);
	if (0 == line) {
		perror("linecap");
		goto close_exit;
	}
	char *p = line;
	ssize_t linelen;
	while (EOF != (c = fgetc(file))) {
		if (delimiter == c) {
			*p = delimiter, *++p = 0;
			process_line(line, linelen+1);
			p = line;
			linelen = 0;
		} else {
			*p++ = c;
			linelen++;
		}
	}
	free(line);
	if (ferror(file)) {
		perror(filename);
		goto close_exit;
	}
 close_exit:

	fclose(file);
}

void
print_line(const char *line, ssize_t linelen) {
	fwrite(line, 1, linelen, stdout);
	fflush(stdout);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		read_lines(argv[1], 16, '\n', print_line);
	}
	return 0;
}
