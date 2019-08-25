#include <_io_.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if MSVC
#  pragma warning(disable: 4244)
#endif

void
read_line(const char *filename,
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

ssize_t
self_getdelim(char **line,
							size_t *linecap,
							int delimiter,
							FILE *stream) {
	static char *l;
	if (!l) {
		l = malloc(*linecap+1);
	}
	char *p = l;
	ssize_t linelen = 0;
	int ch = fgetc(stream);
	while (delimiter != ch && EOF != ch) {
		*p++ = ch;
		linelen++;
		ch = fgetc(stream);
	}
	if (EOF != ch) {
		*p++ = delimiter;
		linelen++;
	}
	*p = 0;
	*line = l;
	return linelen;
}

void
test_read_line(const char *filename) {
	read_line(filename, 16, '\n', print_line);
}

void
test_getdelim(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *line = 0;
	size_t linecap = 0;
	ssize_t linelen;
	while ((linelen = getdelim(&line, &linecap, '\n', file)) > 0) {
		fwrite(line, linelen, 1, stdout);
	}
	if (line) {
		free(line);
	}
	fclose(file);
}

void
test_self_getdelim(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *line = 0;
	size_t linecap = 0;
	ssize_t linelen;
	while ((linelen = self_getdelim(&line, &linecap, '\n', file)) > 0) {
		fwrite(line, linelen, 1, stdout);
	}
	if (line) {
		free(line);
	}
	fclose(file);	
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		char *f = malloc(strlen(argv[1]) + 1);
		strcpy(f, argv[1]);
		test_read_line(f);
		fprintf(stdout, "##########\n");
		test_getdelim(f);
		fprintf(stdout, "##########\n");
		test_self_getdelim(f);
 		free(f);
	}
	return 0;
}
