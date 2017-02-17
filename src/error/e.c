#include <nm_auto_config.h>
#include <nm_auto_headers.h>
#include <utils.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef CC_MSVC
#pragma warning(disable:4996) /*_CRT_SECURE_NO_WARNINGS*/
#endif

int
main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("input a filename\n");
		return -1;
	}

	FILE* out;
	int e;

	out = fopen(argv[1], "r");
	e = errno;

	if (e) {
		fprintf(stderr, "open %s failed, caused:\n", argv[1]);
		perror(strerror(e));
		return -1;	
	}

	fprintf(stdout, "open %s successed\n", argv[1]);
	e = errno;
	if (e) {
		fprintf(stderr, "open %s failed, caused by %s\n", argv[1], strerror(e));
	}


	fclose(out);
	
	return 0;
}
