#include <_lang_.h>
#include <string.h>
#include <stdio.h>


#if MSVC
/* warning C4996: 'strtok': This function or variable may be
	 unsafe. Consider using strtok_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS */
#  pragma warning(disable : 4996)
#endif

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
