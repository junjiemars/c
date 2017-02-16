#include <io.h>
#include <stdio.h>

int
main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("input a filename\n");
		return -1;
	}

	FILE* out;
	int e1, e2;

	io_fopen(e1, out, argv[1], "r");

	if (e1) {
		io_fprintf(e2, stderr, "open %s failed, caused:\n", argv[1]);
		perror(strerror(e1));
		return -1;	
	}

	io_fprintf(e1, stdout, "open %s successed\n", argv[1]);
	if (e1) {
		io_fprintf(e2, stderr, "open %s failed, caused by %s\n", argv[1], strerror(e1));
	}

	fclose(out);
	
}
