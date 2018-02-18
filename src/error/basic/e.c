#include "_error_.h"
#include <stdio.h>
#include <string.h>

int
main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("input a filename\n");
		return 0;
	}

	FILE* out = 0;
	int e = 0;

	out = fopen(argv[1], "r");
	e = errno;

	if (e) {
		fprintf(stderr, "open %s failed, caused by: %s\n",
            argv[1], strerror(e));
	}

  if (out) {
    fclose(out);
  }

  printf("%i\n", XXX);
}
