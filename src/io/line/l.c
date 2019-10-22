#include <_io_.h>

#if MSVC
#  pragma warning(disable: 4244)
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#elif GCC
#  ifndef _GNU_SOURCE
#    define _GNU_SOURCE 1
#  endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ssize_t
self_getline(char ** restrict linep,
						 size_t * restrict linecapp,
						 FILE * restrict stream) {
	if (0 == *linecapp) {
		*linecapp = 8;
		*linep = malloc(*linecapp);
		if (0 == *linep) {
			return EOF;
		}
	}
	
	ssize_t linelen = 0;
	int c = 0;
	char *p = *linep;
	
	while (EOF != (c = fgetc(stream))) {
		if (linelen == (ssize_t) (*linecapp - 1)) {
			*linecapp <<= 1;
			char *p1 = realloc(*linep, *linecapp);
			if (0 == p1) {
				return EOF;
			}
			p = p1 + linelen;
		}
		*p++ = c;
		linelen++;

		if ('\n' == c) {
			*p = 0;
			return linelen;
		}
	}
	return EOF == c ? EOF : linelen;
}

ssize_t
self_getdelim(char ** restrict linep,
							size_t * restrict linecapp,
							int delimiter,
							FILE * restrict stream) {
	if (0 == *linep) {
		*linecapp = 8;
		*linep = malloc(*linecapp);
		if (0 == *linep) {
			return EOF;
		}
	}

	ssize_t linelen = 0;
	int c = 0;
	char *p = *linep;
	
	while (EOF != (c = fgetc(stream))) {
		if (linelen == (ssize_t) *linecapp - 1) {
			*linecapp <<= 1;
			char *p1 = realloc(*linep, *linecapp);
			if (0 == *p1) {
				return EOF;
			}
			p = p1 + linelen;
		}
		*p++ = c;
		linelen++;
		
		if (delimiter == c) {
			*p = 0;
			return linelen;
		}
	}
	return EOF == c ? EOF : linelen;
}

void
test_getline(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *line = 0;
	size_t linecap = 0;
	ssize_t linelen = 0;
	
	while (0 < (linelen = getline(&line, &linecap, file))) {
		fwrite(line, linelen, 1, stdout);
	}
	
	if (!feof(file)) {
		perror(filename);
	}
	if (line) {
		free(line);
	}
	fclose(file);
}

void
test_getline1(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *line = malloc(8-1);
	size_t linecap = 0;
	ssize_t linelen = 0;
	
	while (0 < (linelen = getline(&line, &linecap, file))) {
		fwrite(line, linelen, 1, stdout);
	}
	
	if (!feof(file)) {
		perror(filename);
	}
	if (line) {
		free(line);
	}
	fclose(file);
}


void
test_self_getline(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *line = malloc(8-1);
	size_t linecap = 8-1;
	ssize_t linelen = 0;
	
	while (0 < (linelen = self_getline(&line, &linecap, file))) {
		fwrite(line, linelen, 1, stdout);
	}
	
	if (!feof(file)) {
		perror(filename);
	}
	if (line) {
		free(line);
	}
	fclose(file);
}


#if !(MSVC)
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
	
	while (0 < (linelen = getdelim(&line, &linecap, '\n', file))) {
		fwrite(line, linelen, 1, stdout);
	}
	if (line) {
		free(line);
	}
	fclose(file);
}
#endif

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
	
	while (0 < (linelen = self_getdelim(&line, &linecap, '\n', file))) {
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
		if (0 == f) {
			perror(argv[1]);
			return 0;
		}
		strcpy(f, argv[1]);
		
		test_getline(f);
		test_getline1(f);
		test_self_getline(f);
		fprintf(stdout, "##########\n");
		
#if !(MSVC)
		test_getdelim(f);
		fprintf(stdout, "##########\n");
#endif
		
		test_self_getdelim(f);
 		free(f);
	}
	return 0;
}
