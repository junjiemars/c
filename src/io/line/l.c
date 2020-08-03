#include <_io_.h>

#if (LINUX)
#  ifndef __USE_GNU
#    define __USE_GNU 1
#  endif
#  ifndef _GNU_SOURCE
#    define _GNU_SOURCE
#  endif
#endif
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <posix/ssize_t.h>

/* #include <unistd.h> */

#define LESS_LEN 7
#define REGU_LEN 8

ssize_t self_getline(char**, size_t*, FILE*);
ssize_t self_getdelim(char**, size_t*, int, FILE*);
void test_getline(const char*);
void test_getline1(const char*);
void test_getline2(const char*);
void test_getdelim(const char*);
void test_self_getdelim(const char*);
void test_self_getline(const char*);

int
main(int argc, char **argv) {

  if (argc < 2) {
    printf("where the file located?\n");
    return 0;
  }

  char *f = malloc(strlen(argv[1]) + 1);
  if (0 == f) {
    perror(argv[1]);
    return 0;
  }
  strcpy(f, argv[1]);
		
  test_getline(f);
  test_getline1(f);
  test_getline2(f);
  test_self_getline(f);
  fprintf(stdout, "##########\n");
		
#if !(MSVC)
  test_getdelim(f);
  fprintf(stdout, "##########\n");
#endif
		
  test_self_getdelim(f);
  free(f);

	return 0;
}

ssize_t
self_getline(char ** restrict linep,
						 size_t * restrict linecapp,
						 FILE * restrict stream) {
  if (0 == linep) {
    return EOF;
  }
	if (0 == *linep) {
		*linecapp = REGU_LEN;
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
      *linep = p1;
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
  if (0 == linep) {
    return EOF;
  }
	if (0 == *linep) {
		*linecapp = REGU_LEN;
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
      *linep = p1;
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

  char *block = 0;
	char **line = &block;
	size_t linecap = 0;
	ssize_t linelen = 0;
	
	while (0 < (linelen = getline(line, &linecap, file))) {
		fwrite(*line, linelen, 1, stdout);
	}
	
	if (ferror(file)) {
		perror(filename);
	}
	fclose(file);
  
  free(*line);
}

void
test_getline1(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *block = malloc(LESS_LEN);
  char **line = &block;
	size_t linecap = LESS_LEN;
	ssize_t linelen = 0;
	
	while (0 < (linelen = getline(line, &linecap, file))) {
		fwrite(*line, linelen, 1, stdout);
	}
	
	if (ferror(file)) {
		perror(filename);
	}
  fclose(file);

  free(*line);
}

void
test_getline2(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

  char *block = 0;
	char **line = &block;
	size_t linecap = 64;
	ssize_t linelen = 0;
	
	while (0 < (linelen = getline(line, &linecap, file))) {
		fwrite(*line, linelen, 1, stdout);
	}
	
	if (ferror(file)) {
		perror(filename);
	}
  fclose(file);
	
  free(*line);
}


void
test_self_getline(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *block = malloc(LESS_LEN);
  char **line = &block;
	size_t linecap = LESS_LEN;
	ssize_t linelen = 0;
	
	while (0 < (linelen = self_getline(line, &linecap, file))) {
		fwrite(*line, linelen, 1, stdout);
	}
	
	if (ferror(file)) {
		perror(filename);
	}
	fclose(file);

  free(*line);
}


#if !(MSVC)
void
test_getdelim(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

  char *block = 0;
	char **line = &block;
	size_t linecap = 0;
	ssize_t linelen;
	
	while (0 < (linelen = getdelim(line, &linecap, '\n', file))) {
		fwrite(*line, linelen, 1, stdout);
	}

  if (ferror(file)) {
    perror(filename);
  }
  fclose(file);

  free(*line);
}
#endif

void
test_self_getdelim(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	char *block = 0;
  char **line = &block;
	size_t linecap = 0;
	ssize_t linelen;
	
	while (0 < (linelen = self_getdelim(line, &linecap, '\n', file))) {
		fwrite(*line, linelen, 1, stdout);
	}

  if (ferror(file)) {
    perror(filename);
  }
  fclose(file);
  
  free(*line);
}

/* eof */
