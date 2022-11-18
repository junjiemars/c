#include "_stdio_.h"


void
test_fgets(const char *filename) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror(filename);
		return;
	}

	int str_len = 128;
	char *str = malloc(str_len);
	if (0 == str) {
		perror("malloc failed");
		return;
	}

	while (0 != (fgets(str, str_len, file))) {
		fwrite(str, strlen(str), 1, stdout);
	}

	if (!feof(file)) {
		perror(filename);
	}
	if (str) {
		free(str);
	}
	fclose(file);
}

int
main(int argc, char **argv)
{
	if (argc > 1) {
		char *f = malloc(strlen(argv[1]) + 1);
		if (0 == f) {
			perror(argv[1]);
			return 0;
		}
		strcpy(f, argv[1]);
		fprintf(stdout, "##########\n");
		test_fgets(f);
		free(f);
	}


	return 0;
}
