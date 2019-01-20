#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define NAME_SIZE 16

typedef struct rect_s {
	char name[NAME_SIZE];
	int width;
	int height;
} rect_s;


void
out(const rect_s *rect, const char *where) {
	FILE *f = fopen(where, "w");
	if (!f) {
		perror(where);
		return;
	}

	size_t len = fwrite((char*)rect, 1, sizeof(rect_s), f);
	if (sizeof(rect_s) != len) {
		if (ferror(f)) {
			perror(where);
		} 
		fprintf(stderr, "!panic: read %zu bytes, but expect %zu bytes\n",
						len, sizeof(rect_s));
	}
	fclose(f);
}

void
in(rect_s *rect, const char *where) {
	FILE *f = fopen(where, "r");
	if (!f) {
		fprintf(stderr, "%s\n", strerror(errno));
		return;
	}

	size_t len = fread((char*)rect, 1, sizeof(rect_s), f);
	if (sizeof(rect_s) != len) {
		fprintf(stderr, "%s\n", "! read rect_s from file failed");
		return;
	}

	fprintf(stdout,"\
rect_s: {\n\
  name: \"%s\",\n\
  width: %i,\n\
  height: %i\n\
}\n", rect->name, rect->width, rect->height);

	fclose(f);
}

int
main(int argc, char **argv) {
	const char *filename = ".rect_s";
	rect_s rect;	
	memset(&rect, 0, sizeof(rect));

	if (argc < 4) {
		/* read from binary file */
		in(&rect, filename);

	} else {
		/* write to binary file */
		strncpy(rect.name, argv[1], NAME_SIZE);
		rect.width = atoi(argv[2]);
		rect.height = atoi(argv[3]);

		out(&rect, filename);
	}

	return 0;
}
