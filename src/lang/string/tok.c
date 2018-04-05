#include <_lang_.h>
#include <string.h>
#include <stdio.h>

int
main(int argc, char **argv) {

	if (argc < 3) {
		printf("usage: string delimeter\n");
		return 1;
	}

	char *s = argv[1];
	char *d = argv[2];

	char *tok = strtok(s, d);
	while (tok) {
		printf(" %s\n", tok);
		tok = strtok(0, d);
	}
}
